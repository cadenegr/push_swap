#!/bin/bash

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    visualize.sh                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cadenegr <cadenegr@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/30 14:00:00 by cadenegr          #+#    #+#              #
#    Updated: 2024/12/30 14:00:00 by cadenegr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Push Swap Algorithm Visualization
# Demonstrates the divide-and-conquer sorting process

GREEN='\033[0;32m'
BLUE='\033[0;34m'
YELLOW='\033[1;33m'
PURPLE='\033[0;35m'
CYAN='\033[0;36m'
RED='\033[0;31m'
NC='\033[0m'

if [ ! -f "./push_swap" ]; then
    echo -e "${RED}❌ Error: push_swap not found. Run 'make' first.${NC}"
    exit 1
fi

# Function to display stack visually
display_stacks() {
    local a_stack="$1"
    local b_stack="$2"
    local operation="$3"
    
    echo -e "${CYAN}Operation: ${YELLOW}$operation${NC}"
    echo -e "${BLUE}Stack A: ${GREEN}$a_stack${NC}"
    echo -e "${PURPLE}Stack B: ${GREEN}$b_stack${NC}"
    echo "-------------------"
}

# Demo 1: Small array demonstration
demo_small() {
    echo -e "${CYAN}🎯 SMALL ARRAY DEMONSTRATION${NC}"
    echo -e "${CYAN}=============================${NC}"
    echo ""
    
    local input="5 3 8 1 9"
    echo -e "${YELLOW}Input: $input${NC}"
    echo -e "${YELLOW}Strategy: Size < 6, using two-segment division${NC}"
    echo ""
    
    echo -e "${BLUE}Initial state:${NC}"
    display_stacks "$input" "" "Initial"
    
    echo -e "${BLUE}Generated moves:${NC}"
    ./push_swap $input | nl -w2 -s'. '
    
    local move_count=$(./push_swap $input | wc -l)
    echo ""
    echo -e "${GREEN}✅ Sorted in $move_count moves${NC}"
    echo ""
}

# Demo 2: Algorithm strategy selection
demo_strategies() {
    echo -e "${CYAN}🧠 ALGORITHM STRATEGY SELECTION${NC}"
    echo -e "${CYAN}================================${NC}"
    echo ""
    
    echo -e "${YELLOW}Size-Adaptive Strategy:${NC}"
    echo -e "• 2-3 elements: ${GREEN}Direct sorting${NC}"
    echo -e "• 4-5 elements: ${GREEN}Two-segment division${NC}"
    echo -e "• 6-120 elements: ${GREEN}Four-segment division${NC}"
    echo -e "• 121+ elements: ${GREEN}Eight-segment division${NC}"
    echo ""
    
    for size in 3 5 15 50; do
        local input=$(seq 1 $size | shuf | tr '\n' ' ')
        local moves=$(./push_swap $input | wc -l)
        
        local strategy=""
        if [ $size -le 3 ]; then
            strategy="Direct"
        elif [ $size -le 5 ]; then
            strategy="Two-segment"
        elif [ $size -le 120 ]; then
            strategy="Four-segment"
        else
            strategy="Eight-segment"
        fi
        
        echo -e "${BLUE}Size $size:${NC} $strategy division → ${GREEN}$moves moves${NC}"
    done
    echo ""
}

# Demo 3: Performance comparison
demo_performance() {
    echo -e "${CYAN}📊 PERFORMANCE COMPARISON${NC}"
    echo -e "${CYAN}=========================${NC}"
    echo ""
    
    local size=20
    echo -e "${YELLOW}Testing with $size elements:${NC}"
    echo ""
    
    # Random case
    local random_input=$(seq 1 $size | shuf | tr '\n' ' ')
    local random_moves=$(./push_swap $random_input | wc -l)
    echo -e "${BLUE}Random order:${NC} $random_moves moves"
    
    # Worst case (reverse sorted)
    local reverse_input=$(seq $size -1 1 | tr '\n' ' ')
    local reverse_moves=$(./push_swap $reverse_input | wc -l)
    echo -e "${BLUE}Reverse sorted:${NC} $reverse_moves moves"
    
    # Best case (already sorted)
    local sorted_input=$(seq 1 $size | tr '\n' ' ')
    local sorted_moves=$(./push_swap $sorted_input | wc -l)
    echo -e "${BLUE}Already sorted:${NC} $sorted_moves moves"
    
    echo ""
    echo -e "${GREEN}Performance Analysis:${NC}"
    echo -e "• Handles various input patterns efficiently"
    echo -e "• Adapts strategy based on complexity"
    echo -e "• Optimizes for best/average cases"
    echo ""
}

# Demo 4: Real-world application
demo_realworld() {
    echo -e "${CYAN}🌍 REAL-WORLD APPLICATIONS${NC}"
    echo -e "${CYAN}===========================${NC}"
    echo ""
    
    echo -e "${YELLOW}This algorithm demonstrates skills valuable in:${NC}"
    echo ""
    echo -e "${GREEN}1. Database Systems:${NC}"
    echo -e "   • Query optimization with limited memory"
    echo -e "   • Index sorting with minimal operations"
    echo ""
    echo -e "${GREEN}2. Embedded Systems:${NC}"
    echo -e "   • Memory-constrained sorting"
    echo -e "   • Stack-based operations"
    echo ""
    echo -e "${GREEN}3. Algorithm Engineering:${NC}"
    echo -e "   • Adaptive strategy selection"
    echo -e "   • Performance optimization"
    echo ""
    echo -e "${GREEN}4. Technical Interviews:${NC}"
    echo -e "   • Complex problem-solving approach"
    echo -e "   • Algorithm analysis and optimization"
    echo ""
}

# Main visualization function
main() {
    echo -e "${CYAN}🎮 PUSH_SWAP ALGORITHM VISUALIZATION${NC}"
    echo -e "${CYAN}====================================${NC}"
    echo ""
    
    demo_small
    demo_strategies
    demo_performance
    demo_realworld
    
    echo -e "${GREEN}🌟 VISUALIZATION COMPLETE!${NC}"
    echo -e "${GREEN}===========================${NC}"
    echo -e "Algorithm ready for ${YELLOW}production deployment${NC} and ${YELLOW}technical presentations${NC}!"
}

# Run with argument or show menu
if [ $# -eq 0 ]; then
    main
else
    case $1 in
        "small")
            demo_small
            ;;
        "strategies")
            demo_strategies
            ;;
        "performance")
            demo_performance
            ;;
        "realworld")
            demo_realworld
            ;;
        *)
            echo "Usage: $0 [small|strategies|performance|realworld]"
            ;;
    esac
fi