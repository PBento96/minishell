## Header files (.h)
```c
#ifndef FILENAME_H				// All header files must have header guards
# define FILENAME_H				// Yes, a space is needed after define

# include <some_bloated_lib.h>	// Includes go at the beginning of the file

# define macro(X) (x)	// Macro Funcs are forbidden (and must be UPPER CASE)
# define TRUE 0			// If you are an evil, but norm compliant person

// Space, not tab, after union, enum, struct and typedef keywords
union u_union
{
	float		f32;
	uint32_t	u32; // This is a very useful union by the way
};

typedef int8_t	t_i8;		// If you are a rust person
t_i8			g_global;	// Forbidden unless stated otherwise

typedef struct s_struct
{
	u_union		my_union_var;
	enum e_enum
	{
		var1,		 // 0 by default
		var2 = 3,	 // 1 by default
	}	my_enum_var; // This enum only exists within the scope of this struct
}	t_structtype;	 // This constructor must be tab aligned
#endif
```

## Source files (.c)
```c
//--tab--// Comments outside of function
void	ft_some_function(int param1, int param2, int param3, int param4)
{ // Maximum of 25 lines, these brackets don't count
	const int	var1 = 3;				// Ok
	static int	var2[3] = {4, 5, 7};	// Ok
	int			var3;					// Ok
	int			var4 = 5;				// Can't declare and initialize :(
	int			var5, var6;				// Multiple declarations per line
	// ----- New empty line here, always after declarations ------
	//... your spaghetti code goes here
}
```