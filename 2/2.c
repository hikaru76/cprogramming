#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char name[32];
    int *subjects;
} student;

int main(void) {
    int		n_student;
    int		n_subject;
	int		i;
	int		j;
	int		sum;
	int		total;
	student	*students;

	printf("Input number of students: ");
	scanf("%d", &n_student);
	printf("Input number of subjects: ");
	scanf("%d", &n_subject);

    students = (student *)calloc(n_student, sizeof(student));
    for (i = 0; i < n_student; i++)
        students[i].subjects = (int*)calloc(n_subject, sizeof(int));

    i = -1;
	while (++i < n_student)
	{
		printf("Input name of No. %d: ", i);
		scanf("%s", students[i].name);
	}
	i = -1;
	while (++i < n_student)
	{
		j = -1;
		while (++j < n_subject)
		{
			printf("Input score of %s's subject%d:", students[i].name, j);
			scanf("%d", &students[i].subjects[j]);
		}
	}

    i = -1;
	total = 0;
	while (++i < n_student)
	{
		j = -1;
		sum = 0;
		while (++j < n_subject)
			sum += students[i].subjects[j];
		printf("%s: Sum %d, Average=%f\n", students[i].name, sum, (double)(sum / n_subject));
		total += sum;
	}
    printf("Total: Sum %d, Avarage=%f\n", total, (double)(total / n_subject / n_student));
    
    for (i = 0; i < n_student; i++) {
        free(students[i].subjects);
    }
    free(students);
}