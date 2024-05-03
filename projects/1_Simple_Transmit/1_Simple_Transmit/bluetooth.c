/******************************************************************************
	Autor:		lau
	Date:		17.1.2016
	HW:			Wasp
	Compiler:	AVR-Studio 6.2
	
	Function:	Vorlage für eine Kommunikation über Bluetooth.
				Der PC muss mit dem Blue-Modul gekoppelt sei.						
				Die Bluetoothverbindung erscheint als serielle COM-Schnittstelle.
******************************************************************************/

#define F_CPU 12000000
#define BAUDRATE 9600

#include "bluetooth.h"

volatile unsigned char bt_rec;

//****************************************************************************************
void bt_init(unsigned long baudrate)
{
	unsigned int my_ubrr = ((F_CPU/8UL/baudrate)-1);	//USART-Vorteiler (für U2X=1)
	UBRRH = ~(1<<URSEL) & (my_ubrr>>8);					//MSByte für Vorteiler, URSEL=0
	UBRRL =  my_ubrr;									//LSByte für Vorteiler
	UCSRA = (1<<U2X);									//"Double-Speed"-Mode aktivieren
	UCSRC = (1<<URSEL)|(1<<UCSZ1)|(1<<UCSZ0);			// asynchroner Mode, Datenformat 8N1
	UCSRB = (1<<RXEN)|(1<<TXEN)|(1<<RXCIE);				//S+E einschalten, E-Interrupt ein
}

//USART Senderoutine
//****************************************************************************************
void bt_putchar(unsigned char data) //Datenbyte übertragen
{
	while ( !( UCSRA & (1<<UDRE)) );	//warten bis Sendepuffer leer ist ("polling")
	UDR = data;							//neue Daten senden
}

//Empfang eines Bytes 
//****************************************************************************************
ISR(USART_RXC_vect)
{
	bt_rec = UDR;
}

//****************************************************************************************
//   PRINTF-Ausgaben
//****************************************************************************************
#include <AVR/io.h>
#include <stdarg.h>

typedef unsigned char  BYTE;
typedef unsigned short WORD;

// Funktionsprototyp der lokalen Hilfsfunktion zur Ausgabe eines Zeichens
static void UartWriteBuf (BYTE *pBuf, int nLen);
static void UartWrite (BYTE c);

// Hilfsvariable zum Zählen der ausgegebenen Zeichen
static WORD	nSent;
static BYTE nFieldWidth;

static struct {
    BYTE fLeftJust:1;   // Feldausrichtung links oder rechts
    BYTE fNegative:1;   // Auszugebende Zahl ist negativ.
} flags;


int bt_printf (const unsigned char *format, ...)
/**********************************************************************
    Einfache Routine, um formatierte Ausgaben auf den UART zu schicken.
    Der Vorteil dieser Routine gegenüber einem sprintf ist dass hier
    kein kostbarer Speicherplatz im SRAM verschwendet wird sondern
    das Resultat wird direkt mit dem UART ausgegeben.
    Der UART muss zuvor korrekt initialisiert werden.

    in   : format    Formatstring, wie von printf her bekannt.
                     Es werden folgende Platzhalterzeichen und Flags
                     erkannt.
                     %c     Einzelnes Zeichen, erwartet char-Argument.
                     %s     Zeichenkette, erwartet char *-Argument
                     %d,%i  Ganzzahl mit Vorzeichen,
                            erwartet int-Argument.
                     %u     Ganzzahl ohne Vorzeichen,
                            erwartet int-Argument
                     %x,%X  Hexzahl (ohne führendes 0x),
                            erwartet int-Argument.
                     %o     Oktalzahl (ohne führendes 0),
                            erwartet int-Argument
                     Ein - nach dem %-Zeichen bedeutet, dass die Ausgabe
                     linksbbündig ausgerichtet ist.
                     Ein Zahlenwert nach dem % bzw. dem - gibt die
                     Breite des Ausgabefeldes an. Die Ausgabe erfolgt
                     falls notwendig auch mit mehr Zeichen.
*/
{
#define SCRATCH 16
    BYTE     scratch[SCRATCH];
    BYTE     format_flag;
    WORD     u_val=0, base;
    BYTE     *ptr;
    va_list  ap;
    BYTE     hexA = 'a';

    nSent = 0;

    va_start (ap, format);
    for (;;) {
        /* In der folgenden Schleife werden alle Zeichen direkt
           weitergegeben, sofern es sich nicht um ein Platzhalterzeichen
           '%' handelt. */
        while ((format_flag = *format++) != '%') {
            if (!format_flag) {   // Ende des Formatstrings erreicht
                va_end (ap);
                return (nSent);
            }
            // Ende des Strings noch nicht erreicht
            // und kein Platzhalterzeichen, also ausgeben
            UartWrite (format_flag);
        }


        // Mit %10s kann beispielsweise ein 4 Zeichen langer String in
        // einem 10 Zeichen langen Feld ausgegeben werden. Zusätzlich
        // kann mit einem - Zeichen die Ausrichtung angegeben werden.
        // UartPrintF ("%10s", "Hallo")  ergibt "     Hallo"
        // UartPrintF ("%-10s", "Hallo") ergibt "Hallo     "
        // Desweiteren kann mit %05d angegeben werden, dass ein Zahlwenwert
        // in einem rechtsbündigen Feld der Länge 5 ausgegeben wird wobei
        // links mit Nullen aufgefüllt wird.
        format_flag = *format++;
        if (format_flag == '-') {
            flags.fLeftJust = 1;
            format_flag = *format++;
        }
        else flags.fLeftJust = 0;

        nFieldWidth = 0;
        while (format_flag >= '0' && format_flag <= '9') {
           nFieldWidth *= 10;
           nFieldWidth += format_flag - '0';
           format_flag = *format++;
        }

        switch (format_flag) {
            case 'c':
                format_flag = va_arg (ap, int);
            default:
                UartWriteBuf (&format_flag, 1);
                continue;
            case 's':
                ptr = va_arg (ap, char *);
                UartWriteBuf (ptr, -1);
                continue;
            case 'o':
                base = 8;
                goto CONVERSION_LOOP;
            case 'i':
            case 'd':
            case 'u':
                base = 10;
                goto CONVERSION_LOOP;
            case 'X':
                hexA = 'A';
                // Weiter wie 'x'
            case 'x':
                base = 16;
CONVERSION_LOOP:
                u_val = va_arg (ap, int);
                flags.fNegative = 0;
                if (format_flag == 'd' || format_flag == 'i') {
                    // Negative Werte auswerten
                    if (((int) u_val) < 0) {
                        flags.fNegative = 1;
                        u_val = -u_val;
                    }
                }
                // Der Scratchpuffer wird von rechts nach links aufgefüllt
                // beginnend mit dem niederwertigsten Digit.
                ptr = scratch + SCRATCH;
                *--ptr = 0;     // Abschliessendes NULL-Byte eintragen
                do {
                    char ch = u_val % base + '0';
                    if (ch > '9') ch += hexA - '9' - 1;
                    *--ptr = ch;
                    u_val /= base;
                } while (u_val);

                if (flags.fNegative) *--ptr = '-';
                UartWriteBuf (ptr, -1);    // Scratchpuffer ausgeben
        }
     }

} /* end of UartPrintF */



static void UartWriteBuf (BYTE *pBuf, int nLen)
/**********************************************************************
    Schreibt einen Puffer auf den UART. Dabei werden die Feldbreite und
    -ausrichtung berücksichtigt.

   in   : pBuf   Adresse der auszugebenden Daten.
   in   : nLen   Anzahl auszugebende Zeichen. Wird hier -1 angegeben
                 so wird ausgegeben bis ein NULL-Zeichen gefunden wird.
*/
{
    BYTE *p;
    int   n;

    if (nLen == -1) {
       // Länge bestimmen
       p = pBuf;
       nLen = 0;
       while (*p++) nLen++;
    }

    // Feld bei Bedarf links auffüllen
    if (!flags.fLeftJust) {
        for (n=nLen; n < nFieldWidth; n++) UartWrite (' ');
    }

    // Pufferinhalt schreiben
    for (n=0; n < nLen; n++) UartWrite (*pBuf++);

    // Feld bei Bedarf rechts auffüllen
    if (flags.fLeftJust) {
        for (n=nLen; n < nFieldWidth; n++) UartWrite (' ');
    }

} /* end of Blank */



static void UartWrite (BYTE c)
/**********************************************************************
    Gibt ein Zeichen auf den UART aus und wartet, bis das Zeichen in
    das Transmit Shift Register uebernommen wurde.
*/
{
    UDR=c;
    // warten, bis das Datenregister des UART leer ist. Dies wird
    // durch Bit 5 (UDRE) im UART Status Register angezeigt.

		while(!((UCSRA & 0x20)==0x20));  	//Warten bis letztes Zeichen gesendet
    nSent++;

} /* end of UartWrite */
