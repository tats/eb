/*                                                            -*- C -*-
 * Copyright (c) 2001
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
 *     initexit
 * ��:
 *     initexit
 * ����:
 *     EB �饤�֥��ν������������򤷤Ƥߤޤ���
 *     �ץ����γ�¦���鸫��С�����ϲ��ΰ�̣��ʤ�ư��Ǥ���
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

    /* EB �饤�֥���������*/
    error_code = eb_initialize_library();
    if (error_code != EB_SUCCESS) {
	fprintf(stderr, "%s: failed to initialize EB Library, %s: %s\n",
	    argv[0], eb_error_message(error_code), argv[1]);
	exit(1);
    }

    /* EB �饤�֥������Ѥ�λ��*/
    eb_finalize_library();
    exit(0);
}
