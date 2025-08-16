# Program to reverse array

## 1. Reversing character array (string)
### Program 1:
```
#include <stdio.h>
#include <string.h>

char *reverse_string(char *str)
{
	char temp = 0;
	int length = strlen(str);
	int start = 0;
	int end = length - 1;

	/* Model 1 */
	while (start < end) {
		/* Swap characters at start and end */
		temp = str[start];
		str[start] = str[end];
		str[end] = temp;

		/* Move start and end towards the center */
		start++;
		end--;
	}

	/* Model 2 */
	while (start < end) {
		/* XOR swap elements at start and end */
		str[start] ^= str[end];
		str[end] ^= str[start];
		str[start] ^= str[end];

		/* move start and end towards the center */
		start++;
		end--;
	}

	return;
}

int main()
{
	char str[] = "Hello, World!";

	printf("Original string: %s\n", str);

	reverse_string(str);

	printf("Reversed string: %s\n", str);

	return 0;
}
```

## 2. Reversing integer array
```
#include <stdio.h>

void reverse_array(int arr[], int size)
{
	int temp = 0;
	int start = 0;
	int end = size - 1;

	/* Model 1 */
	while (start < end) {
		/* Swap elements at start and end */
		temp = arr[start];
		arr[start] = arr[end];
		arr[end] = temp;

		/* Move start and end towards the center */
		start++;
		end--;
	}

	/* Model 2 */
	while (start < end) {
		/* XOR swap elements at start and end */
		arr[start] ^= arr[end];
		arr[end]   ^= arr[start];
		arr[start] ^= arr[end];

		/* Move start and end towards the center */
		start++;
		end--;
	}

	/* Model 3 */
	int i = 0;

	for(i = 0; i < size/2; i++){
		temp = arr[i];
		arr[i] = arr[size - i - 1];
		arr[size - i - 1] = temp;
	}

	return;
}

int main()
{
	int arr[] = {1, 2, 3, 4, 5};
	int size = sizeof(arr) / sizeof(arr[0]);

	printf("Original Array: ");
	for (int i = 0; i < size; i++) {
		printf("%d ", arr[i]);
	}

	reverse_array(arr, size);

	printf("\nReversed Array: ");
	for (int i = 0; i < size; i++) {
		printf("%d ", arr[i]);
	}

	return 0;
}
```
