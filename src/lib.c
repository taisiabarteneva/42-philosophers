# include "philo.h"

static int	ft_isdigit(int c)
{
    if (c >= '0' && c < '9')
        return (SUCCESS);
    return (FAILURE);
}

static int	check_rmd(const char *str)
{
    int	flag;
    int	i;

    flag = 0;
    i = 0;
    while (str[i] != '\0')
    {
        if (ft_isdigit(str[i]) == FAILURE)
            flag = 1;
        i++;
    }
    return (flag);
}

long	ft_atoi(const char *str)
{
    long	val;
    int		sign;

    val = 0;
    sign = 1;
    while (*str == ' ' || (*str >= 9 && *str <= 13))
        str++;
    if (*str == '-')
        sign *= -1;
    if (*str == '-' || *str == '+')
        str++;
    while (*str >= '0' && *str <= '9')
    {
        val = val * 10 + *str - '0';
        str++;
    }
    return (val * sign);
}

int ft_is_numeric_arg(const char *str)
{
    while (*str == ' ' || (*str >= 9 && *str <= 13))
        str++;
    if 	(*str == '-' || *str == '+')
        str++;
    return (check_rmd(str));
}

