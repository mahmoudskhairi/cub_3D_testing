#include <stdio.h>
#include <stdlib.h>
// #include <st.h>

void	*ft_memcpy(void *s1, const void *s2, size_t n)
{
	size_t			i;
	char	*ps1;
	char	*ps2;

	i = 0;
	ps1 = ( char *) s1;
	ps2 = ( char *) s2;
	if (s1 == s2)
		return (s1);
	if (!ps1 && !ps2)
		return (NULL);
	while (i < n)
	{
		ps1[i] = ps2[i];
		i++;
	}
	return (s1);
}

int main()
{
	char s[10] = "hellot";
	unsigned char s2[10] = "€€€€";
	printf("%s\n", s2);
	// printf("%s\n", ft_memcpy(s, s2, 6));
}