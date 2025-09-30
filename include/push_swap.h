/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <neo_dgri@hotmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 18:16:28 by cadenegr          #+#    #+#             */
/*   Updated: 2025/09/30 12:25:43 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file push_swap.h
 * @brief Advanced Divide-and-Conquer Sorting Algorithm Implementation
 * 
 * This header defines the interface for a sophisticated sorting algorithm
 * that uses only two stacks and a limited set of operations. The implementation
 * demonstrates enterprise-level algorithmic thinking and optimization strategies.
 * 
 * @algorithm Adaptive Divide-and-Conquer with Size-Based Strategy Selection
 * @complexity Best: O(n), Average: O(n log n), Worst: O(n²)
 * @memory O(n) auxiliary space for sorted reference array
 * 
 * @author cadenegr <cadenegr@student.42berlin.de>
 * @version 2.0 Enterprise Edition
 * @date 2024-12-30
 */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

/* ************************************************************************** */
/*                                INCLUDES                                    */
/* ************************************************************************** */

# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <limits.h>
# include <unistd.h>
# include <sys/wait.h>

/* ************************************************************************** */
/*                                CONSTANTS                                   */
/* ************************************************************************** */

/** @brief Maximum supported input size */
# define MAX_SIZE 1000

/** @brief Strategy thresholds for algorithm selection */
# define DIRECT_SORT_THRESHOLD    4    // Direct sorting for tiny inputs
# define TWO_SEGMENT_THRESHOLD    6    // Two-segment division for small inputs  
# define FOUR_SEGMENT_THRESHOLD   121  // Four-segment division for medium inputs
                                       // Eight-segment for large inputs (121+)

/* ************************************************************************** */
/*                              DATA STRUCTURES                              */
/* ************************************************************************** */

/**
 * @brief Local variables structure for function optimization
 * 
 * Reduces parameter passing overhead by grouping commonly used
 * temporary variables. This approach improves performance in
 * tight loops and recursive functions.
 */
typedef struct s_local_variables
{
	int		i;         /**< Primary loop counter */
	int		j;         /**< Secondary loop counter */
	int		k;         /**< Tertiary loop counter */
	int		temp;      /**< Temporary value storage */
	int		length;    /**< Current segment length */
	int		count;     /**< Operation counter */
	bool	turn_on;   /**< State flag for optimization logic */
}	t_v;

/**
 * @brief Global algorithm state and data storage
 * 
 * Central data structure containing all algorithm state, input data,
 * and optimization arrays. Designed for efficient memory access
 * patterns and algorithm performance.
 */
typedef struct s_global_variables
{
	long	long_array[MAX_SIZE];    /**< Input validation with overflow detection */
	int		original_array[MAX_SIZE]; /**< Preserved original input sequence */
	int		sorted_array[MAX_SIZE];   /**< Reference sorted array for optimization */
	int		temp[MAX_SIZE];          /**< Temporary working array */
	int		size;                    /**< Current problem size */
	int		low;                     /**< Current segment lower bound */
	int		high;                    /**< Current segment upper bound */
	int		moves;                   /**< Total moves counter for performance tracking */
	int		counter;                 /**< Algorithm state counter */
}	t_g;

/**
 * @brief Stack data structure for sorting operations
 * 
 * Implements efficient stack operations with array-based storage.
 * Optimized for the specific operations required by the push_swap
 * algorithm (push, pop, rotate, reverse rotate).
 */
typedef struct s_stack
{
	int	top;           /**< Stack pointer (index of top element) */
	int	s[MAX_SIZE];   /**< Stack storage array */
}	t_s;

/* ************************************************************************** */
/*                            FUNCTION DECLARATIONS                          */
/* ************************************************************************** */

/* ═══════════════════════════════════════════════════════════════════════ */
/*                          INPUT PROCESSING & VALIDATION                   */
/* ═══════════════════════════════════════════════════════════════════════ */

/**
 * @brief Main argument processor and validator
 * @param argc Argument count from main
 * @param argv Argument vector from main  
 * @param g Global state structure to populate
 * @return 1 on success, 0 on error
 * 
 * Handles all input validation, duplicate detection, and integer
 * overflow protection. Sets up sorted reference array for optimization.
 */
int		argument_processor(int argc, char **argv, t_g *g);

/**
 * @brief Process single string argument with space-separated numbers
 * @param argv Single argument string to parse
 * @param g Global state to populate
 */
void	two_arguments(char *argv, t_g *g);

/**
 * @brief Process multiple individual number arguments
 * @param argc Number of arguments
 * @param argv Array of argument strings
 * @param g Global state to populate
 * @return 1 on success, 0 on error
 */
int		more_arguments(int argc, char **argv, t_g *g);

/**
 * @brief Calculate range bounds for optimization
 * @param g Global state containing the data
 */
void	low_high_values(t_g *g);

/* ═══════════════════════════════════════════════════════════════════════ */
/*                            ERROR HANDLING & VALIDATION                   */
/* ═══════════════════════════════════════════════════════════════════════ */

/**
 * @brief Validate argument string format
 * @param argv Argument string to validate
 * @return true if valid, false otherwise
 */
bool	correct_arguments(char *argv);

/**
 * @brief Validate parsed parameters
 * @param g Global state to validate
 * @return true if valid, false otherwise
 */
bool	parameters(t_g *g);

/**
 * @brief Check for integer overflow in input
 * @param g Global state containing parsed values
 * @return true if all values fit in int, false otherwise
 */
bool	int_size(t_g *g);

/**
 * @brief Detect duplicate values in input
 * @param g Global state to check
 * @return true if no duplicates, false if duplicates found
 */
bool	duplicate(t_g *g);

/* ═══════════════════════════════════════════════════════════════════════ */
/*                              STACK OPERATIONS                            */
/* ═══════════════════════════════════════════════════════════════════════ */

/**
 * @brief Initialize stack pointer
 * @param top Pointer to stack top index
 */
void	initialize_stack(int *top);

/**
 * @brief Check if stack is full
 * @param top Pointer to stack top index
 * @return true if full, false otherwise
 */
bool	is_full(int *top);

/**
 * @brief Check if stack is empty
 * @param top Pointer to stack top index  
 * @return true if empty, false otherwise
 */
bool	is_empty(int *top);

/**
 * @brief Push element onto stack
 * @param stack Stack array
 * @param top Pointer to stack top index
 * @param value Value to push
 */
void	push(int *stack, int *top, int value);

/**
 * @brief Pop element from stack
 * @param stack Stack array
 * @param top Pointer to stack top index
 * @return Popped value
 */
int		pop(int *stack, int *top);

/* ═══════════════════════════════════════════════════════════════════════ */
/*                           STACK INITIALIZATION                           */
/* ═══════════════════════════════════════════════════════════════════════ */

/**
 * @brief Initialize both stacks for algorithm execution
 * @param g Global state
 * @param a Stack A structure
 * @param b Stack B structure
 */
void	init_stacks(t_g *g, t_s *a, t_s *b);

/**
 * @brief Build initial stack A from input data
 * @param g Global state containing input
 * @param s Stack structure to populate
 */
void	build_a_stack(t_g *g, t_s *s);

/* ═══════════════════════════════════════════════════════════════════════ */
/*                        SORTING ALGORITHM DIRECTORS                       */
/* ═══════════════════════════════════════════════════════════════════════ */

/**
 * @brief Main sorting algorithm director
 * @param g Global algorithm state
 * @param a Stack A
 * @param b Stack B
 * 
 * Implements size-adaptive strategy selection:
 * - Size < 4: Direct sorting
 * - Size < 6: Two-segment division  
 * - Size < 121: Four-segment division
 * - Size ≥ 121: Eight-segment division
 */
void	sort(t_g *g, t_s *a, t_s *b);

/**
 * @brief Direct sorting for tiny inputs (2-3 elements)
 * @param g Global state
 * @param a Stack A to sort
 */
void	just_sort(t_g *g, t_s *a);

/**
 * @brief Optimized 3-element sorting
 * @param g Global state
 * @param a Stack A to sort
 */
void	sort_three(t_g *g, t_s *a);

/**
 * @brief Small input sorting with two-segment strategy
 * @param g Global state
 * @param a Stack A
 * @param b Stack B
 */
void	sort_small(t_g *g, t_s *a, t_s *b);

/**
 * @brief Medium input sorting with four-segment strategy
 * @param g Global state
 * @param a Stack A
 * @param b Stack B
 */
void	four(t_g *g, t_s *a, t_s *b);

/**
 * @brief Large input sorting with eight-segment strategy
 * @param g Global state
 * @param a Stack A  
 * @param b Stack B
 */
void	eight(t_g *g, t_s *a, t_s *b);

/* ═══════════════════════════════════════════════════════════════════════ */
/*                      PUSH_SWAP ALLOWED OPERATIONS                       */
/* ═══════════════════════════════════════════════════════════════════════ */

/**
 * @brief Swap first two elements of stack A
 * @param a Stack A
 * @param g Global state for move counting
 */
void	sa(t_s *a, t_g *g);

/**
 * @brief Rotate stack A (first element becomes last)
 * @param a Stack A
 * @param g Global state for move counting
 */
void	ra(t_s *a, t_g *g);

/**
 * @brief Reverse rotate stack A (last element becomes first)
 * @param a Stack A
 * @param g Global state for move counting
 */
void	rra(t_s *a, t_g *g);

/**
 * @brief Push top element from A to B
 * @param a Source stack A
 * @param b Destination stack B
 * @param g Global state for move counting
 */
void	pb(t_s *a, t_s *b, t_g *g);

/**
 * @brief Swap first two elements of stack B
 * @param b Stack B
 * @param g Global state for move counting
 */
void	sb(t_s *b, t_g *g);

/**
 * @brief Rotate stack B (first element becomes last)
 * @param b Stack B
 * @param g Global state for move counting
 */
void	rb(t_s *b, t_g *g);

/**
 * @brief Reverse rotate stack B (last element becomes first)
 * @param b Stack B
 * @param g Global state for move counting
 */
void	rrb(t_s *b, t_g *g);

/**
 * @brief Push top element from B to A
 * @param b Source stack B
 * @param a Destination stack A
 * @param g Global state for move counting
 */
void	pa(t_s *b, t_s *a, t_g *g);

/**
 * @brief Simultaneous sa and sb operations
 * @param a Stack A
 * @param b Stack B
 * @param g Global state for move counting
 */
void	ss(t_s *a, t_s *b, t_g *g);

/**
 * @brief Simultaneous ra and rb operations
 * @param a Stack A
 * @param b Stack B
 * @param g Global state for move counting
 */
void	rr(t_s *a, t_s *b, t_g *g);

/**
 * @brief Simultaneous rra and rrb operations
 * @param a Stack A
 * @param b Stack B
 * @param g Global state for move counting
 */
void	rrr(t_s *a, t_s *b, t_g *g);

/* ═══════════════════════════════════════════════════════════════════════ */
/*                        DIVIDE-AND-CONQUER ALGORITHMS                     */
/* ═══════════════════════════════════════════════════════════════════════ */

/**
 * @brief Check if stack is already sorted
 * @param a Stack to check
 * @return true if sorted, false otherwise
 */
bool	is_it_sorted(t_s *a);

/**
 * @brief Two-segment division algorithm for small inputs
 * @param g Global state
 * @param a Stack A
 * @param b Stack B
 */
void	divide(t_g *g, t_s *a, t_s *b);

/**
 * @brief Four-segment division algorithm for medium inputs
 * @param g Global state
 * @param a Stack A
 * @param b Stack B
 * @param multiplier Division factor for segment sizing
 */
void	divide_four(t_g *g, t_s *a, t_s *b, int multiplier);

/**
 * @brief Find element position in sorted reference array
 * @param array Stack array to search in
 * @param top Stack top index
 * @param g Global state containing sorted reference
 * @return Position index in sorted array
 * 
 * @note Optimization opportunity: This linear search could be
 *       replaced with hash table lookup for O(1) performance
 */
int		search(int *array, int top, t_g *g);

/**
 * @brief Sort elements in stack B by relative position
 * @param g Global state
 * @param b Stack B
 * @param divider Threshold for high/low classification
 */
void	sort_high_and_low(t_g *g, t_s *b, int divider);

/**
 * @brief Transfer sorted elements from B back to A
 * @param g Global state
 * @param b Source stack B
 * @param a Destination stack A
 */
void	sort_to_a(t_g *g, t_s *b, t_s *a);

/**
 * @brief Handle remaining elements in four-segment division
 * @param g Global state
 * @param a Stack A
 * @param b Stack B
 */
void	push_rest_of_div_four(t_g *g, t_s *a, t_s *b);

/**
 * @brief Eight-segment division algorithm for large inputs
 * @param g Global state
 * @param a Stack A
 * @param b Stack B
 * @param multiplier Division factor for segment sizing
 */
void	divide_eight(t_g *g, t_s *a, t_s *b, int multiplier);

/**
 * @brief Continue eight-segment division process
 * @param g Global state
 * @param a Stack A
 * @param b Stack B
 * @param divider Current division threshold
 */
void	continue_div_eight(t_g *g, t_s *a, t_s *b, int divider);

/**
 * @brief Transfer elements from B to A in organized blocks
 * @param g Global state
 * @param a Destination stack A
 * @param b Source stack B
 * @param divider Block size parameter
 */
void	send_to_a_by_blocks(t_g *g, t_s *a, t_s *b, int divider);

/**
 * @brief Sort elements from low to high values
 * @param a Stack A
 * @param g Global state
 * @param divider Sort threshold
 */
void	sort_low_to_high(t_s *a, t_g *g, int divider);

/**
 * @brief Handle four-segment division specific sorting
 * @param g Global state
 * @param b Stack B
 * @param a Stack A
 */
void	sort_if_div_four(t_g *g, t_s *b, t_s *a);

/**
 * @brief Check element position from bottom of stack
 * @param b Stack B
 * @param value Target value
 * @return Position from bottom
 */
int		check_from_zero(t_s *b, int value);

/**
 * @brief Check element position from top of stack
 * @param b Stack B
 * @param value Target value
 * @return Position from top
 */
int		check_from_top(t_s *b, int value);

/* ═══════════════════════════════════════════════════════════════════════ */
/*                              UTILITY FUNCTIONS                           */
/* ═══════════════════════════════════════════════════════════════════════ */

/**
 * @brief Debug function to print current stack states
 * @param a Stack A
 * @param b Stack B
 * @param g Global state
 */
void	print(t_s *a, t_s *b, t_g *g);

#endif /* PUSH_SWAP_H */