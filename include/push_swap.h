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
 * @brief Block division sort: push_swap with two stacks and 11 operations
 * 
 * Stack A is sent to B in blocks of ranks. Inside B every block is split
 * in 2 (low half rotated to the bottom). Then the biggest number of B is
 * pulled back to A, one by one, until A is sorted.
 * 
 * @algorithm Block division (blocks = ~0.4 * sqrt(n)) + greedy pull back
 * @moves     100 numbers: ~580 on average, 500 numbers: ~5100 on average
 * @memory    Fixed arrays of MAX_SIZE, no malloc
 * 
 * @author cadenegr <cadenegr@student.42berlin.de>
 * @version 3.0
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
# define DIRECT_SORT_THRESHOLD    4    // 2-3 numbers: direct sort
# define TWO_SEGMENT_THRESHOLD    6    // 4-5 numbers: smallest to b, sort 3
                                       // 6+ numbers: block division

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
 * - Size < 6: Smallest numbers to B, sort 3, push back
 * - Size ≥ 6: Block division (divide_blocks) + pull back (pull_back)
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
/*                         BLOCK DIVISION ALGORITHM                         */
/* ═══════════════════════════════════════════════════════════════════════ */

/**
 * @brief Check if stack is already sorted
 * @param a Stack to check
 * @return true if sorted, false otherwise
 */
bool	is_it_sorted(t_s *a);

/**
 * @brief Small inputs (4-5): send the smallest to B until 3 are left
 * @param g Global state
 * @param a Stack A
 * @param b Stack B
 */
void	divide(t_g *g, t_s *a, t_s *b);

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
 * @brief Number of blocks for a given size (about 0.4 * sqrt(size))
 * @param size Amount of numbers to sort
 * @return Block count (100 -> 4, 500 -> 9)
 */
int		how_many_blocks(int size);

/**
 * @brief Send A to B block by block, splitting every block in 2
 * @param g Global state
 * @param a Stack A
 * @param b Stack B
 * @param blocks Number of rank blocks
 *
 * Block i holds ranks [size*(i-1)/blocks, size*i/blocks). After pb, the
 * low half of the block is rotated to the bottom of B (rb), so B ends up
 * as small piles. An rb followed by an ra is merged into rr.
 */
void	divide_blocks(t_g *g, t_s *a, t_s *b, int blocks);

/**
 * @brief Pull the biggest number of B back to A until B is empty
 * @param g Global state
 * @param b Stack B
 * @param a Stack A
 *
 * Rotates B the short way. If the second biggest is closer it is pushed
 * first, then the biggest, and sa puts them in order.
 */
void	pull_back(t_g *g, t_s *b, t_s *a);

/**
 * @brief Small inputs: bring B back to A, biggest first
 * @param g Global state
 * @param b Source stack B
 * @param a Destination stack A
 */
void	sort_to_a(t_g *g, t_s *b, t_s *a);

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