/*
 * Filename:
 *     disctype.c
 *
 * Usage:
 *     disctype book-path
 *
 * Example:
 *     disctype /cdrom
 *
 * Description:
 *     This program shows disc type (EB/EBG/EBXA/EBXA-C/S-EBXA or
 *     EPWING) of a CD-ROM book.  `book-path' points to the top
 *     directory of the CD-ROM book where the file CATALOG or CATALOGS
 *     resides.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>

#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif

#include <eb/eb.h>
#include <eb/error.h>

int
main(argc, argv)
    int argc;
    char *argv[];
{
    EB_Book book;
    EB_Disc_Code disc_code;

    /*
     * Check for command line arguments.
     */
    if (argc != 2) {
	fprintf(stderr, "Usage: %s book-path\n", argv[0]);
	exit(1);
    }

    /*
     * Initialize `book'.
     */
    eb_initialize(&book);

    /*
     * Bind a book.  Exit if it fails.
     */
    if (eb_bind(&book, argv[1]) == -1) {
	fprintf(stderr, "%s: failed to bind the book: %s\n",
	    argv[0], argv[1]);
	exit(1);
    }

    /*
     * Show disc type.
     */
    disc_code = eb_disc_type(&book);
    fputs("disc type: ", stdout);
    if (disc_code == EB_DISC_EB) {
	fputs("EB/EBG/EBXA", stdout);
    } else if (disc_code == EB_DISC_EPWING) {
	fputs("WPING", stdout);
    } else {
	fputs("unknown", stdout);
    }
    fputc('\n', stdout);

    /*
     * Clear the book.
     */
    eb_clear(&book);

    exit(0);
}
