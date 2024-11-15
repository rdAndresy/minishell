int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		c = 'a' + (c - 'A');
	return (c);
}
