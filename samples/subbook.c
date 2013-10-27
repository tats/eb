/*                                                            -*- C -*-
 * Copyright (c) 1999, 2000, 01 
 *    Motoyuki Kasahara
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

/*
 * ������ˡ:
 *     subbook <book-path>
 * ��:
 *     subbook /cdrom
 * ����:
 *     <boook-path> �ǻ��ꤵ�� CD-ROM ���Ҥ˴ޤޤ�Ƥ��뤹�٤Ƥ����ܤ�
 *     ��̾��ɽ�����ޤ���
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
    EB_Error_Code error_code;
    EB_Book book;
    EB_Subbook_Code subbook_list[EB_MAX_SUBBOOKS];
    int subbook_count;
    char title[EB_MAX_TITLE_LENGTH + 1];
    int i;

    /* ���ޥ�ɹ԰���������å���*/
    if (argc != 2) {
	fprintf(stderr, "Usage: %s book-path\n", argv[0]);
	exit(1);
    }

    /* EB �饤�֥��� `book' ��������*/
    error_code = eb_initialize_library();
    if (error_code != EB_SUCCESS) {
	fprintf(stderr, "%s: failed to initialize EB Library, %s: %s\n",
	    argv[0], eb_error_message(error_code), argv[1]);
	goto die;
    }
    eb_initialize_book(&book);

    /* ���Ҥ� `book' �˷���դ��롣*/
    error_code = eb_bind(&book, argv[1]);
    if (error_code != EB_SUCCESS) {
	fprintf(stderr, "%s: failed to bind the book, %s: %s\n",
	    argv[0], eb_error_message(error_code), argv[1]);
	goto die;
    }

    /* ���ܤΰ����������*/
    error_code = eb_subbook_list(&book, subbook_list, &subbook_count);
    if (error_code != EB_SUCCESS) {
	fprintf(stderr, "%s: failed to get the subbbook list, %s\n",
	    argv[0], eb_error_message(error_code));
	goto die;
    }

    /* ���Ҥ˴ޤޤ�Ƥ������ܤ���̾����ϡ�*/
    for (i = 0; i < subbook_count; i++) {
	error_code = eb_subbook_title2(&book, subbook_list[i], title);
	if (error_code != EB_SUCCESS) {
	    fprintf(stderr, "%s: failed to get the title, %s\n",
		argv[0], eb_error_message(error_code));
	    continue;
	}
	printf("%d: %s\n", i, title);
    }

    /* ���Ҥ� EB �饤�֥������Ѥ�λ��*/
    eb_finalize_book(&book);
    eb_finalize_library();
    exit(0);

    /* ���顼ȯ���ǽ�λ����Ȥ��ν�����*/
  die:
    eb_finalize_book(&book);
    eb_finalize_library();
    exit(1);
}
