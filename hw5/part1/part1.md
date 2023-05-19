B103040001 孫世諭

# Part1

## Question 1
Symbolic link is a kind of soft link which like a shortcut of the target file, hard link uses the same inode of the target file instead.

### Advantage of symbolic link
It's able to link to another directory or file. hard link can't do.

### Advantage of hard link
Hard link has no space and time cost, compared to symbolic link.

## Question 2

### A
(0.02+5+10)*100 = 1502 ms

### B
(0.02+0.1*2+10)*100 = 1022 ms

## Question 3

| Frame | LRU | Optimal |
| ----- | --- | ------- |
| 1     | 20  | 20      |
| 2     | 18  | 15      |
| 3     | 15  | 11      |
| 4     | 10  | 8       |
| 5     | 8   | 7       |
| 6     | 7   | 7       |
| 7     | 7   | 7       |

## Question 4

### a

contiguous: 201
linked: 1
indexed: 1

### b

contiguous: 101
linked: 52
indexed: 1

### c

contiguous: 1
linked: 3
indexed: 1

### d

contiguous: 0
linked: 1
indexed: 0

### e

contiguous: 98
linked: 52
indexed: 0

## Question 5

1. make 11123456 into binary(or hex): 0b0000 0000 1010 1001 1011 1011 0000 0000 
2. the highest 20 bits is the index of page table.
3. the lowest 12 bits is the offset of physical page.

### Hardware
address transform (dynamically)

### Software
page IO


