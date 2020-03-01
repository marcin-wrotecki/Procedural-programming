
// Implementacja kolejki FIFO przy wykorzystaniu tablic
// Implementation of FIFO queue using arrays

#include "FIFO.h"
#define MAXSIZE 10

int main()
{
	QueueFIFO queue;

	if (!QfCreate(&queue, MAXSIZE))
	{
		perror("ERROR-WRONG MEMORY ALLOCATION");
	}
	//queue.MaxQueueSize = 10;

	printf("MAXSIZE: %d \n", queue.MaxQueueSize);

	if (QFEmpty(&queue))
		printf("Queue is empty\n");

	printf("Adding 4 elements\n");
	QFIFOITEM* a = CreateElement(5);
	QFEnqueue(&queue, *a);
	a = CreateElement(6);
	QFEnqueue(&queue, *a);
	a = CreateElement(7);
	QFEnqueue(&queue, *a);
	a = CreateElement(8);
	QFEnqueue(&queue, *a);
	QFPrint(queue);
	printf("Current size: %d \n", queue.CurrentQueueSize);


	printf("Dequeue element: %d\n", QFDequeue(&queue));
	printf("Dequeue element: %d\n", QFDequeue(&queue));
	printf("Current size: %d \n", queue.CurrentQueueSize);

	QFPrint(queue);

	printf("Remove first element: \n");

	QFDel(&queue);
	QFPrint(queue);
	printf("Current size: %d \n", queue.CurrentQueueSize);

	printf("Clear queue\n");
	QFClear(&queue);
	if (QFEmpty(&queue))
		printf("Queue is empty \n");
	printf("Removing queue\n");
	QFRemove(&queue);


}