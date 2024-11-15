int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		c = 'A' + (c - 'a');
	return (c);
}
