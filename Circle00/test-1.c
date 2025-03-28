/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbui-min <fbui-min@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 17:00:59 by fbui-min          #+#    #+#             */
/*   Updated: 2025/03/26 15:10:01 by fbui-min         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LOWEST -200
#define HIGHEST 200
#define ARR_SIZE 10
#define LEN 1

size_t	strcount(char const *s, char c)
{
	size_t	i;
	size_t	count;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c)
			count++;
		while (s[i] != c && s[i])
			i++;
		while (s[i] == c && s[i])
			i++;
	}
	return (count);
}

int	main(void)
{
	printf("%zu\n", strcount("abcabca",'c'));
	printf("%zu\n", strcount("abc",'c'));
	printf("%zu\n", strcount("abcac",'c'));
	printf("%zu\n", strcount("cabcac",'c'));
	printf("%zu\n", strcount("c",'c'));
	printf("%zu\n", strcount("",'c'));
	//printf("%-10dgtyg\n", 100);

	/*
	// display non printable characters
	char	*str = "";
	printf("%c\n", str[0]);
	printf("%d\n", str[0]);
	*/

	/*
	int	i = -0;
	printf("%d\n", i);
	printf("%s\n%s\n%s", ft_itoa(-623), ft_itoa(-156), ft_itoa(-0));
	*/

	/*
	int	num = -12345;
	int	i = 0;
	printf("%d\n", 123 / 10);
	printf("%d\n", 123 % 10);

	while (num != 0)
	{
		num /= 10;
		i++;
	}
	printf("%d", i);
	*/

	/*
	printf("%d\n", ft_atoi("-2147483648"));
	printf("%d", atoi("-2147483648"));
	*/

	/*
	char *s1 = "   \t  \n\n \t\t  \n\n\nHello \t  Please\n Trim me !\n   \n \n \t\t\n  ";

	char *ret = ft_strtrim(s1, " \n\t");
	printf("%s", ret);
	if (ret == ((void *)0))
		printf("\nTEST_SUCCESS");
	printf("\nTEST_FAILED");
	*/
	//char *s1 = "\t   \n\n\n  \n\n\t    Hello \t  Please\n Trim me !\t\t\t\n  \t\t\t\t  ";
	//char *s2 = "Hello \t  Please\n Trim me !";
	//int r_size = strlen(s2);
	//int size;

	//printf("%s", ft_strtrim(s1, " \n\t"));

	/*
	char s1[] = "abababaabNo, my name is Phongbaa";
	printf("%s\n", s1);
	printf("%s\n", ft_strtrim(s1, "ab"));
	*/
	/*
	const char *haystack = "Hello, this is a simple example.";
	const char *needle = "simple";
	char *result = strnstr(haystack, needle, 50);

	if (result != NULL) {
		printf("Found '%s' in haystack: %s\n", needle, result);
	} else {
		printf("'%s' not found in the first 20 characters.\n", needle);
	}
	

	char str1[] = "Hello";
    char str2[] = "Hello";

    // Compare the first 5 characters of str1 and str2
    int result = strncmp(str1, str2, 5);

    if (result == 0)
        printf("The first 5 characters are the same.\n");
    else
        printf("The first 5 characters are different.\n");
	*/
	
	/*
	char	*s1 = NULL;

	ft_memchr(s1, 'a', 2);
	printf("%s\n", s1);
	
	char str[] = "Hello";
	printf("Size of str: %zu\n", sizeof(str));
	*/
	
	/*
	char	str1[20] = "abcde";

	ft_memmove(str1 + 2, str1, 1);
	printf("%s", str1);
	*/
	
	/*
	char *str1 = "Hello world!";
	char *str2 = str1 + 5;
	printf("%s\n", str2);
	*/

	/*
	char *str1 = "abc";
	char *str2 = "abb";
	printf("%i\n", memcmp(str1, str2, 3));
	*/

	/*
	char myStr[] = "Hello World!";
	char *myPtr = (char*)ft_memchr(myStr, 'o', 12);
	if (myPtr != NULL)
		printf("%s", myPtr);
	*/
	
	/*
	size_t	i;

	i = 5;
	while (i--)
		printf("%i\n", (int)i);

	i = 5;
	printf("\n");
	while (--i)
		printf("%i\n", (int)i);

	i = 5;
	printf("\n");
	while (i)
	{
		printf("%i\n", (int)i);
		i--;
	}
		*/

	/*
	// LOCATE OCCURRENCE OF C TEST
	char myStr[] = "Hello World";
	printf("%s\n", ft_memchr(myStr, 'o', 4));
	printf("%s\n", memchr(myStr, 'o', 4));
	printf("%s\n", ft_strchr(myStr, 'o'));
	printf("%s\n", ft_strrchr(myStr, 'o'));
	*/

	/*
	// MEMSET TEST
	char	str1[ARR_SIZE];
	char	str2[ARR_SIZE];
	//char	*str3;
	printf("Arr1\n");
	for (int i = 0; i < ARR_SIZE; i++)
		printf("%i - %c\n", i, str1[i]);
		printf("Arr2\n");
	for (int i = 0; i < ARR_SIZE; i++)
		printf("%i - %c\n", i, str2[i]);
	ft_memset(str1, 'a', sizeof(str1));
	memset(str2, 'a', LEN);
	//ft_memset(str3, 'a', LEN);
	//memset(str3, 'a', LEN);
	printf("my buffer: %s\n", str1);
	printf("or buffer: %s\n", str2);
	//printf("my buffer: %s\n", str3);
	//printf("or buffer: %s\n", str3);
	*/

	/*
	char myStr[] = "Hello World";
	char *myPtr = ft_strchr(myStr, 'l');
	if (myPtr != NULL)
		printf("%s", myPtr);
	
	int		l;
	int		count;
	int		countoriginal;
	char	*src;
	char	dst[20];

	l = LOWEST;
	count = 0;
	countoriginal = 0;
	while (l <= HIGHEST)
	{
		if (ft_isalpha(l) == 1)
			count++;
		if (isalpha(l) == 1)
			countoriginal++;
		l++;
	}
	printf("+-------------------------+\n");
	printf("| ISALPHA\n");
	printf("| Myf %i\n", count);
	printf("| Originf %i\n", countoriginal);
	count = 0;
	countoriginal = 0;
	while (l <= HIGHEST)
	{
		if (ft_isdigit(l) == 1)
			count++;
		if (isdigit(l) == 1)
			countoriginal++;
		l++;
	}
	printf("+-------------------------+\n");
	printf("| ISDIGIT\n");
	printf("| Myf %i\n", count);
	printf("| Originf %i\n", countoriginal);
	src = "abcdefgh";
	printf("+-------------------------+\n");
	printf("| MEMCPY\n");
	printf("| Myf %s\n", memcpy(dst, src, ARR_SIZE));
	printf("| Originf %s\n", ft_memcpy(dst, src, ARR_SIZE));
	*/
	return (0);
}
