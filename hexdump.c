/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hexdump.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: at0m <at0m741@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 00:24:06 by at0m              #+#    #+#             */
/*   Updated: 2023/08/10 00:54:15 by at0m             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

void    printHex(const void *data, size_t size)
{
    unsigned char *bytes = (unsigned char *) data;
    size_t i = 0;

    while (i < size)
    {
        printf("0x%016X ", (unsigned int)i);
        size_t j = 0;
        while (j < 16 && i + j < size)
        {
            printf ("%02X ", bytes[i + j]);
            j++;
        }
        while (j < 16)
        {
            printf("    ");
            j++;
        }
        printf("| ");
        j = 0;
        while (j < 16 && i + j < size)
        {
            if (bytes[j + i] >= 32 && bytes[i + j] <= 126)
            {
                printf("%c", bytes[i + j]);
            }
            else
            {
                printf(".");
            }
            j++;
        }
        printf("\n");
        i += 16;
    }
}

int     main(int argc, char **argv)
{
    if (argc != 3)
    {
        printf("usage : %s <binary> <size>", argv[0]);
        printf("no such file");
        return 1;
    }
    FILE *fptr;
    fptr = fopen(argv[1], "rb");

    if (fptr == NULL)
    {
        printf("error");
        return 1;
    }

    fseek(fptr, 0, SEEK_END);
    long filesize = ftell(fptr);
    fseek(fptr, 0, SEEK_SET);
    
    unsigned char *buffer = malloc(filesize);
    if (buffer == NULL)
    {
        printf("Malloc error");
        return 1;
    }
    fread(buffer, 1, filesize, fptr);
    fclose(fptr);

    size_t dumpsize = atoi(argv[2]);
    if (dumpsize > filesize)
    {
        dumpsize = filesize;
    }
    

    printHex(buffer, dumpsize);

    free(buffer);
    return 0;    
}
