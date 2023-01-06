#include "philo_bonus.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;
	size_t			i;

	if (!n)
		return (0);
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	while ((str1[i] == str2[i]) && (i < (n -1)) && str1[i] && str2[i])
		i++;
	return (str1[i] - str2[i]);
}

static unsigned int	math(const char *s, int i)
{
	int	x;

	x = 0;
	while ('0' <= s[i] && s[i] <= '9')
	{
		x *= 10;
		x += s[i] - '0';
		i++;
	}
	return (x);
}

int	ft_atoi(const char	*str)
{
	int		i;
	int		j;
	int		x;
	char	*s;

	if (!(str))
		return (0);
	i = 0;
	j = 0;
	s = (char *)str;
	while (s[i] == 32 || (9 <= s[i] && 13 >= s[i]))
		i++;
	if (s[i] == '-' && ++i)
		j++;
	else if (s[i] == '+')
		i++;
	if (!ft_strncmp(&str[i], "-2147483648", 12))
		return (-2147483648);
	x = math(s, i);
	if (j % 2)
		x = -x;
	return (x);
}
