/* Simple reverse-polish calculator */

#include <ctype.h>
#include <stdio.h>

class Stack {
public:
	Stack() { top = 0; }
	void push(int data);
	int pop();
	void show() const;
private:
	int array[10];
	unsigned top;
};

void Stack::push(int data)
{
	if (top < sizeof(array) / sizeof(array[0])) {
		array[top] = data;
		top++;
	} else {
		printf("stack overflow\n");
	}
}

int Stack::pop()
{
	int data;
	if (top != 0) {
		top--;
		data = array[top];
	} else {
		printf("stack empty\n");
		data = 0;
	}
	return data;
}

void Stack::show() const
{
	if (top != 0) {
		unsigned i = 0;
		do {
			printf("%d ", array[i]);
			i++;
		} while (i < top);
		printf("\n");
	}
}

int main()
{
	int c;
	int temp;
	bool quit = false;
	printf("Enter reverse-polish expressions, q to quit\n");
	Stack stack;
	while (!quit &&
		(c = fgetc(stdin)) != EOF)
	{
		switch (c) {
		case ' ':
		case '\n':
			break;

		case '0': case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9':
			temp = 0;
			for (; isdigit(c); c = fgetc(stdin)) {
				temp = temp * 10 + (c - '0');
			}
			ungetc(c, stdin);
			stack.push(temp);
			break;

		case '+':
			stack.push(stack.pop() + stack.pop());
			break;

		case '*':
			stack.push(stack.pop() * stack.pop());
			break;

		case '-':
			temp = stack.pop();
			stack.push(stack.pop() - temp);
			break;

		case '/':
			temp = stack.pop();
			if (temp == 0)
				printf("division by zero\n");
			else
				stack.push(stack.pop() / temp);
			break;

		case '=':
			temp = stack.pop();
			stack.push(temp);
			printf("%d\n", temp);
			break;

		case 's':
			stack.show();
			break;

		case 'q':
			quit = true;
			break;

		default:
			printf("unrecognized: %c\n", c);
			break;
		}
	}
	return 0;
}
