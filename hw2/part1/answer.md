B103040001 孫世諭

# Part1

## Question 1

MIPS Instructions (pesudo code):
```
enter_region:
	addiu $REG, $zero, 1
	xor $REG, $REG, $LOCK
	xor $LOCK, $REG, $LOCK
	xor $REG, $REG, $LOCK
	bne $REG, $zero, enter_region

	jr $ra
```
- 1\. enter_region
- 2\. make ```$REG``` to 1
- 3\. ~ 5. swap
- 6\. if locked back to enter_region

## Question 2

### (a)
T / (T+S)

### (b)
T / (T+S)

### (c)
T / (T + (T/Q)*S)

### (d)
Because of T=S so:
T / (T + (T/Q)*Q)
= T / T+T
= 1 / 2

### (e)
Because of Q->0
T / (T + (T/Q)*S) lim Q->0
= T / (T + MAX)
= T / MAX
= 0


## Question 3
use ```pthread``` to achieve:

```c
pthread_t mailbox_A, mailbox_B;
```
the messages can be received by ```mailbox_A``` and ```mailbox_B``` individually.
	

## Question 4

(Q4 picture.jpg)


```
A = 1
B = 1
C = 2
D = 2
```
