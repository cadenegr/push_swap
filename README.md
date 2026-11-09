# push_swap

[![42 School](https://img.shields.io/badge/42-School_Project-000000?style=for-the-badge&logo=42&logoColor=white)](https://42.fr/)
[![C](https://img.shields.io/badge/c-%2300599C.svg?style=for-the-badge&logo=c&logoColor=white)](https://en.wikipedia.org/wiki/C_(programming_language))

Sort a list of integers using two stacks and a fixed set of 11 operations, in as few operations as possible. This is the 42 school `push_swap` project, solved with my own algorithm: **blocks that cross between the stacks and split in 2 every time**.

| Numbers | Average moves | Worst seen | 42 full-score limit |
|---|---|---|---|
| 3 | 1 | 2 | 3 |
| 5 | 8 | 10 | 12 |
| 100 | ~620 | 684 | 700 |
| 500 | ~5 255 | 5 443 | 5 500 |

Worst seen over more than 1 400 random runs of 100 numbers and more than 900 random runs of 500 numbers. Every run is replayed move by move to check that the stack really ends up sorted. `sa` is only used for 2 to 5 numbers.

## The rules

Two stacks, **A** and **B**. A starts with the numbers, B starts empty. The program prints the operations that sort A in ascending order, with the smallest number on top.

| Operation | Effect |
|---|---|
| `sa` `sb` `ss` | swap the top two numbers of A, of B, or of both |
| `pa` `pb` | move the top number of B onto A, or of A onto B |
| `ra` `rb` `rr` | rotate up: the top number goes to the bottom (A, B, both) |
| `rra` `rrb` `rrr` | rotate down: the bottom number goes to the top (A, B, both) |

## The algorithm

Every number is looked at by its **rank**: its position in the sorted list (0 = smallest, 499 = biggest for 500 numbers). A **block** is a range of ranks, for example 100–199.

### Step 1: A → B, 5 blocks, each split in 2 → 10 blocks (`divide_four`)

A is scanned 5 times, once per block of ranks: 0–99, 100–199, 200–299, 300–399, 400–499.

- A number of the current block → `pb`.
- Any other number → `ra`, keep scanning.

Right after `pb`, the block is **split in 2**:

- the low part of the block (its first 45 %, for example 100–144) → `rb`, it goes to the bottom of B
- the high part (145–199) stays on top

When an `rb` is followed by an `ra`, both are done at once with `rr`. After 5 passes, B holds **10 blocks**: high parts stacked on top, low parts stacked at the bottom.

### Step 2: B → A, every block split in 2 → 20 blocks (`divide_eight`)

Every block crosses back to A, **biggest block first**. Thanks to step 1, the next block is always either on top of B or at its bottom:

- on top → `pa` directly
- at the bottom → `rrb` brings each number up first, then `pa`

On the way, every block is split in 2 again at its own split point: low part → `ra` (bottom of A), high part stays on top. A now holds **20 blocks**.

### Step 3: A → B, every block split in 2 → 40 blocks (`divide_eight`)

The same crossing again, A → B, **smallest block first** (`rra` for blocks at the bottom of A, `rb` for the low parts). B now holds **40 blocks** of about 12 numbers each, in an order where the big blocks sit at the top and at the bottom of B.

### Step 4: pull back (`sort_if_div_four`)

The biggest number left in B is brought to the top with `rb` or `rrb`, whichever is shorter, and pushed with `pa`. A is filled from the top, so it ends up sorted. Because the blocks are small and the big ones are at the ends of B, the biggest number is always close.

```
             A                     B
start        500 numbers           -
step 1       -                     10 blocks   (5 passes over A, split in 2)
step 2       20 blocks             -           (biggest block first)
step 3       -                     40 blocks   (smallest block first)
step 4       sorted                -           (biggest number first)
```

### Up to 120 numbers

Only step 1 and step 4 (`four()` in [src/sort_tree.c](src/sort_tree.c)). For 100 numbers, two extra crossings cost more than they save.

### 2 to 5 numbers

- **2–3 numbers:** sorted directly with `sa` / `ra` / `rra` (2 moves at most).
- **4–5 numbers:** the smallest numbers go to B until 3 are left, those 3 are sorted, and B comes back (10 moves at most).

## Why these numbers

The two tuning values are in [include/push_swap.h](include/push_swap.h):

```c
# define FIRST_BLOCKS    5    // blocks of the first crossing, each split in 2
# define SPLIT_PERCENT   45   // low part of a block sent to the bottom when splitting
```

**Why 2 crossings and not more.** Each crossing costs about the same, ~1 000 moves for 500 numbers: every number is pushed once, and about half need a rotation. The blocks get smaller with every crossing, so the pull-back gets cheaper, but by less each time. The first pair of crossings saves far more than it costs; the second pair costs more than it saves. Measured with 4 first blocks:

| Crossings after step 1 | Crossings cost | Pull back | Total (500 numbers) |
|---|---|---|---|
| 0 | — | 5 663 | 7 039 |
| **2** | ~1 925 | 2 035 | **5 335** |
| 4 | ~3 870 | 1 054 | 6 314 |

**Why 5 first blocks and a 45 % split.** More first blocks means more `ra` while scanning A; fewer means bigger blocks to pull back. Splitting a little under the middle means fewer numbers need the rotation to the bottom. Average over 40 runs of 500 numbers:

| First blocks | Split 50 % | Split 45 % | Split 40 % |
|---|---|---|---|
| 4 | 5 330 | 5 274 | 5 283 |
| 5 | 5 320 | **5 264** | 5 266 |

## Build and run

```bash
git clone https://github.com/cadenegr/push_swap.git
cd push_swap
make
./push_swap 5 3 8 1 9          # prints the moves, one per line
./push_swap "5 3 8 1 9"        # numbers in one argument also work
./push_swap 1 2 2              # prints "Error" on stderr
```

Invalid input (letters, duplicates, numbers outside the `int` range, a lone `-`, an empty argument, more than 1000 numbers) prints `Error` followed by a newline on stderr. No input, or input that is already sorted, prints nothing.

## Testing

```bash
make test        # input error checks + full sorting suite
make benchmark   # sorting suite only
make validate    # 20 runs of 100 numbers, limit 700
make stress      # 100 runs of 500 numbers, limit 5500
make help        # all targets
```

The checker ([tester/checker.py](tester/checker.py), Python 3) runs `push_swap` and replays every printed move on its own copy of the stacks. A run fails if:
- the program crashes, exits with an error, or writes to stderr
- A is not sorted or B is not empty at the end
- a move is unknown
- the move count is over the limit

You can also call it directly:

```bash
python3 tester/checker.py 500 100 5500   # 100 runs of 500 numbers, limit 5500
```

## Visualizer

```bash
make visual                # or: ./visualize.sh
./visualize.sh 20 100      # choose the sizes
./visualize.sh -n 5 3 8 1  # choose the exact numbers
```

This runs `push_swap`, saves the runs to `visualizer/data.js` and opens [visualizer/index.html](visualizer/index.html) in your browser. You can play, pause, step with ← →, change the speed, or drag through the run. Each number is a bar: longer and warmer means bigger.

With 500 numbers you can watch the blocks cross: everything goes to B, comes back to A, goes to B again, and gets smaller every time. The strip at the bottom shows the whole run (`pb` blue, `pa` orange, rotations grey); click it to jump.

You can also open `visualizer/index.html` on its own: it shows a sample run of 500 numbers, and **Paste a run** accepts the numbers plus any program's output.

## Project layout

```
push_swap/
├── Makefile
├── benchmark.sh            input checks + sorting suite (make test)
├── visualize.sh            runs push_swap and opens the visualizer
├── include/
│   ├── push_swap.h         structures, tuning values, documented prototypes
│   └── libft.h
├── src/
│   ├── push_swap.c         main: parse, build stack A, sort
│   ├── argument_processor.c  read numbers from one or many arguments
│   ├── error_handle.c      input validation (format, int range, duplicates)
│   ├── build_stacks.c      fill stack A
│   ├── stack_functions.c   push / pop / is_empty / is_full
│   ├── a_stack_fts.c       sa ra rra pb
│   ├── b_stack_fts.c       sb rb rrb pa
│   ├── both_a_b_stack_fts.c  ss rr rrr
│   ├── sort_tree.c         picks the strategy by size: four() or eight()
│   ├── sort_two_div.c      2–5 numbers
│   ├── four_div.c          step 1: A -> B in blocks, split in 2
│   ├── sort_eight_div.c    steps 2 and 3: blocks cross and split in 2
│   └── sort_four_div.c     step 4: pull the biggest number back to A
├── tester/
│   └── checker.py          replays the moves and checks the result
├── visualizer/
│   ├── index.html          the visualizer page
│   └── sample-data.js      sample run shown when no data.js exists
└── libft/                  my C library (with ft_printf)
```

## History

**v2, the version I submitted at 42.** Same idea: 4 blocks to B, 8 to A, 16 to B, then pull back. But the block split had a bug. The split point was `divider / 2`, counted from 0 instead of from the start of the current block, so only the first block was split correctly. Every later block landed without being split, and `eight()` was built by hand around that.

**v3.1, this version.** One `divide_eight()` crossing that splits every block at its own split point, so it works for any number of crossings. Plus tuning (5 first blocks, 45 % split) and fixes:
- a hang with 4 numbers
- `Error` now on stderr
- stricter input checks
- quoted lists anywhere in the arguments
- `make` no longer relinks, and rebuilds when a header changes

| | v2 | v3.1 |
|---|---|---|
| 100 numbers | 727 avg, 802 max | ~620 avg, 684 max |
| 500 numbers | 7 982 avg, 8 325 max | ~5 255 avg, 5 443 max |
| 4 numbers | hung on 23 of 24 orders | 7 moves max |
