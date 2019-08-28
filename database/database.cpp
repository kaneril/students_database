// database.cpp: ���������� ����� ����� ��� ����������� ����������.
//
#include "stdafx.h"
#include <stdio.h> 
#include <conio.h> 
#include <string.h> 
#include <Windows.h> 
#include <cmath> 
#include <locale.h>

//�������� �������� 
//������, ���������� ��� ������ � ��������
typedef struct questionnaire
{
	int id;
	char surname[25], name[20], patronymic[25], sex[4], phone[14], mail[30];
} Quest;
// �����������, ����� �������� ����� �� ����� ������ ��� id
typedef union field
{
	char surname[25], name[20], patronymic[25], sex[4], phone[14], mail[30];
} Field;
//�������� ��������� ��� ������ � �������
typedef struct basic
{
	int id;
	Field f;
} Basic;
//��������� ��� ����� �� ������� ���������
typedef struct basic_list
{
	Basic b;
	struct basic_list *ptr_b;
} Basic_list;

//���������� �������
//�������� ������� ��� ������ � �����
//�������� �� ����������� � ����
int check_id(FILE *, FILE *);
//����� �� id
void search_by_id(FILE *, FILE *, FILE *, FILE *, FILE *, FILE *, FILE *, FILE *);
//�������� �� id
void del_by_id(FILE *, FILE *, FILE *, FILE *, FILE *, FILE *, FILE *, FILE *);
//���������� ������ ��������
void add(FILE *, FILE *, FILE *, FILE *, FILE *, FILE *, FILE *, FILE *);
//����� �� ������ ���� ����
void print_all(FILE *, FILE *, FILE *, FILE *, FILE *, FILE *, FILE *, FILE *, FILE *);
//����� �� ���
void search_by_name(FILE *, FILE *, FILE *, FILE *, FILE *, FILE *, FILE *, FILE *);

//��������������� �������
//��� ������
//���������� ������ ��������
Basic_list * addelem(Basic_list *, FILE *);
//������������� ������
Basic_list * init(FILE *);
//������ ������
void listprint(Basic_list *, FILE *);
//������������ ������
Basic_list * form_list(FILE *);
//�������� �������� �� �����
void del_file(int, FILE *, char *);
//�������� �������� �� ������
Basic_list * delelem(int, Basic_list *);

int main()
{
	//���������� ������� ���� 
	/*SetConsoleCP(1251);
	SetConsoleOutputCP(1251);*/
	setlocale(LC_ALL, "Rus");
	//��������� ���������� 
	FILE *f_sname, *f_name, *f_patr, *f_sex, *f_phone, *f_mail, *f_id_b, *f_id_f, *f_print;
	int i = 0;

	//��������� ����� 
	fopen_s(&f_sname, "surname.txt", "r+");
	fopen_s(&f_name, "name.txt", "r+");
	fopen_s(&f_patr, "patronymic.txt", "r+");
	fopen_s(&f_sex, "sex.txt", "r+");
	fopen_s(&f_phone, "phone.txt", "r+");
	fopen_s(&f_mail, "mail.txt", "r+");
	fopen_s(&f_id_b, "id_busy.txt", "r+");
	fopen_s(&f_id_f, "id_free.txt", "r+");
	fopen_s(&f_print, "print_all.txt", "w");

	//�������� �������� ������ 
	if (f_sname == NULL) {
		printf("������ �������� ����� surname.txt \n");
	}
	else
	{
		printf("���� surname.txt ������ \n");
	};
	if (f_name == NULL) {
		printf("������ �������� ����� name.txt \n");
	}
	else
	{
		printf("���� name.txt ������ \n");
	};
	if (f_patr == NULL) {
		printf("������ �������� ����� patronymic.txt \n");
	}
	else
	{
		printf("���� patronymic.txt ������ \n");
	};
	if (f_sex == NULL) {
		printf("������ �������� ����� sex.txt \n");
	}
	else
	{
		printf("���� sex.txt ������ \n");
	};
	if (f_phone == NULL) {
		printf("������ �������� ����� phone.txt \n");
	}
	else
	{
		printf("���� phone.txt ������ \n");
	};
	if (f_mail == NULL) {
		printf("������ �������� ����� mail.txt \n");
	}
	else
	{
		printf("���� mail.txt ������ \n");
	};
	if (f_id_b == NULL) {
		printf("������ �������� ����� id_busy.txt \n");
	}
	else
	{
		printf("���� id_busy.txt ������ \n");
	};
	if (f_id_f == NULL) {
		printf("������ �������� ����� id_free.txt \n");
	}
	else
	{
		printf("���� id_free.txt ������ \n");
	};
	if (f_print == NULL) {
		printf("������ �������� ����� print_all.txt \n");
	}
	else
	{
		printf("���� print_all.txt ������ \n");
	};

	printf_s("\n");
	printf_s("���� ��������� ������ 13558/2\n");

	do
	{
		printf_s("\n");
		printf_s("�������� ��������:\n1 ��������� ���� �� ���� id � ����\n2 ������� �� ������ ������ �� id\n3 �������� ������ �� id\n4 ����� �������� �� ��� \n5 �������� ����� �������\n6 ������� �� ������ ��� ����\n7 ��������� �����\n");
		printf_s("������� ��� ���������� ��������:");
		scanf_s("%i", &i);
		printf_s("\n");
		switch (i) {
		case 1:
		{
			if (check_id(f_id_b, f_id_f) == 0)
			{
				printf_s("����� id � ���� ���");
			}
			else
			{
				printf_s("���� id � ���� ����\n");
			}

		};
		break;
		case 2:
		{
			search_by_id(f_sname, f_name, f_patr, f_sex, f_phone, f_mail, f_id_b, f_id_f);
		};
		break;
		case 3:
		{
			del_by_id(f_sname, f_name, f_patr, f_sex, f_phone, f_mail, f_id_b, f_id_f);
		};
		break;
		case 4:
		{
			search_by_name(f_sname, f_name, f_patr, f_sex, f_phone, f_mail, f_id_b, f_id_f);
		};
		break;
		case 5:
		{
			add(f_sname, f_name, f_patr, f_sex, f_phone, f_mail, f_id_b, f_id_f);
		};
		break;
		case 6:
		{
			print_all(f_sname, f_name, f_patr, f_sex, f_phone, f_mail, f_id_b, f_id_f, f_print);
		};
		break;
		case 7:	break;
		default:
			printf_s("������ �������� ��� ��������\n");
		};
		printf_s("\n");
	} while (i != 7);

	//��������� ����� 
	fclose(f_sname);
	printf("���� surname.txt ������ \n");
	fclose(f_name);
	printf("���� name.txt ������ \n");
	fclose(f_patr);
	printf("���� patronymic.txt ������ \n");
	fclose(f_sex);
	printf("���� sex.txt ������ \n");
	fclose(f_phone);
	printf("���� phone.txt ������ \n");
	fclose(f_mail);
	printf("���� mail.txt ������ \n");
	fclose(f_id_b);
	printf("���� id_busy.txt ������ \n");
	fclose(f_id_f);
	printf("���� id_free.txt ������ \n");
	fclose(f_print);
	printf("���� print_all.txt ������ \n");
	return 0;
}

//���������� �������
//��� ����
int check_id(FILE *f_id_b, FILE *f_id_f)
{
	int flag = 1, id = 0, i = 0;
	char c;
	printf_s("������� id:");
	scanf_s("%d", &id);
	fscanf_s(f_id_f, "%d", &i);
	if (id >= i)
	{
		flag = 1;
	}
	else
	{
		do
		{
			fscanf_s(f_id_b, "%d", &i);
			if (i > id)
			{
				break;
			};
			if (i = id)
			{
				flag = 0;
				break;
			}
			c = fgetc(f_id_b);
			fseek(f_id_b, -1, SEEK_CUR);
		} while (c != EOF);

	};
	fseek(f_id_b, 0, SEEK_SET);
	fseek(f_id_f, 0, SEEK_SET);
	if (flag == 0)
	{
		return(id);
	}
	else
	{
		return(0);
	}
}
void search_by_id(FILE *f_sname, FILE *f_name, FILE *f_patr, FILE *f_sex, FILE *f_phone, FILE *f_mail, FILE *f_id_b, FILE *f_id_f)
{
	Quest *q;
	int id;
	q = (Quest*)malloc(sizeof(Quest));
	id = check_id(f_id_b, f_id_f);
	if (id == 0)
	{
		printf_s("����� id � ���� ���");
	}
	else
	{
		do
		{
			fscanf_s(f_sname, "%d", &(*q).id);
			fgets((*q).surname, 25, f_sname);
			fscanf_s(f_name, "%d", &(*q).id);
			fgets((*q).name, 20, f_name);
			fscanf_s(f_patr, "%d", &(*q).id);
			fgets((*q).patronymic, 25, f_patr);
			fscanf_s(f_sex, "%d", &(*q).id);
			fgets((*q).sex, 4, f_sex);
			fscanf_s(f_phone, "%d", &(*q).id);
			fgets((*q).phone, 14, f_phone);
			fscanf_s(f_mail, "%d", &(*q).id);
			fgets((*q).mail, 30, f_mail);
		} while ((*q).id != id);
		fseek(f_sname, 0, SEEK_SET);
		fseek(f_name, 0, SEEK_SET);
		fseek(f_patr, 0, SEEK_SET);
		fseek(f_sex, 0, SEEK_SET);
		fseek(f_phone, 0, SEEK_SET);
		fseek(f_mail, 0, SEEK_SET);
		printf_s("������ �������� ��������\n");
		printf_s("id: %d\nsurname: %s\nname: %s\npatronymic: %s\nsex: %s\nphone: %s\nmail: %s\n", (*q).id, (*q).surname, (*q).name, (*q).patronymic, (*q).sex, (*q).phone, (*q).mail);
	}
}
void del_by_id(FILE *f_sname, FILE *f_name, FILE *f_patr, FILE *f_sex, FILE *f_phone, FILE *f_mail, FILE *f_id_b, FILE *f_id_f)
{
	int id;
	char *str;
	id = check_id(f_id_b, f_id_f);
	if (id == 0)
	{
		printf_s("����� id � ���� ���");
	}
	else
	{
		str = "surname.txt";
		del_file(id, f_sname, str);
		str = "name.txt";
		del_file(id, f_name, str);
		str = "patronymic.txt";
		del_file(id, f_patr, str);
		str = "sex.txt";
		del_file(id, f_sex, str);
		str = "phone.txt";
		del_file(id, f_phone, str);
		str = "mail.txt";
		del_file(id, f_mail, str);
		str = "id_busy.txt";
		del_file(id, f_id_b, str);
		printf_s("������ ������� �� ����\n");
	}
}
void add(FILE *f_sname, FILE *f_name, FILE *f_patr, FILE *f_sex, FILE *f_phone, FILE *f_mail, FILE *f_id_b, FILE *f_id_f)
{
	Basic *q;
	q = (Basic*)malloc(sizeof(Basic));
	fseek(f_id_f, 0, SEEK_SET);
	fscanf_s(f_id_f, "%d", &(*q).id);
	fseek(f_id_f, 0, SEEK_SET);
	fprintf(f_id_f, "%d", (*q).id + 1);
	fseek(f_id_b, 0, SEEK_END);
	fprintf(f_id_b, "%d\n", (*q).id);
	printf_s("������� ������ ��������\n");
	printf_s("�������: ");
	fgets((*q).f.surname, 25, stdin);
	fgets((*q).f.surname, 25, stdin);
	fseek(f_sname, 0, SEEK_END);
	fprintf(f_sname, "%d %s", (*q).id, (*q).f.surname);
	printf_s("���: ");
	fgets((*q).f.name, 20, stdin);
	fseek(f_name, 0, SEEK_END);
	fprintf(f_name, "%d %s", (*q).id, (*q).f.name);
	printf_s("��������: ");
	fgets((*q).f.patronymic, 25, stdin);
	fseek(f_patr, 0, SEEK_END);
	fprintf(f_patr, "%d %s", (*q).id, (*q).f.patronymic);
	printf_s("���: ");
	fgets((*q).f.sex, 4, stdin);
	fseek(f_sex, 0, SEEK_END);
	fprintf(f_sex, "%d %s", (*q).id, (*q).f.sex);
	printf_s("�������: ");
	fgets((*q).f.phone, 14, stdin);
	fseek(f_phone, 0, SEEK_END);
	fprintf(f_phone, "%d %s", (*q).id, (*q).f.phone);
	printf_s("E-mail: ");
	fgets((*q).f.mail, 30, stdin);
	fseek(f_mail, 0, SEEK_END);
	fprintf(f_mail, "%d %s", (*q).id, (*q).f.mail);
	printf_s("������ �������� � ����\n�������� id: %d", (*q).id);
	//��������� ����� 
	fclose(f_sname);
	fclose(f_name);
	fclose(f_patr);
	fclose(f_sex);
	fclose(f_phone);
	fclose(f_mail);
	fclose(f_id_b);
	fclose(f_id_f);
	//��������� ����� 
	fopen_s(&f_sname, "surname.txt", "r+");
	fopen_s(&f_name, "name.txt", "r+");
	fopen_s(&f_patr, "patronymic.txt", "r+");
	fopen_s(&f_sex, "sex.txt", "r+");
	fopen_s(&f_phone, "phone.txt", "r+");
	fopen_s(&f_mail, "mail.txt", "r+");
	fopen_s(&f_id_b, "id_busy.txt", "r+");
	fopen_s(&f_id_f, "id_free.txt", "r+");
}
void print_all(FILE *f_sname, FILE *f_name, FILE *f_patr, FILE *f_sex, FILE *f_phone, FILE *f_mail, FILE *f_id_b, FILE *f_id_f, FILE *f_print)
{
	fprintf(f_print, "���� ������ ���������\n");
	Quest *q;
	char c;
	q = (Quest*)malloc(sizeof(Quest));
	fseek(f_sname, 0, SEEK_SET);
	fseek(f_name, 0, SEEK_SET);
	fseek(f_patr, 0, SEEK_SET);
	fseek(f_sex, 0, SEEK_SET);
	fseek(f_phone, 0, SEEK_SET);
	fseek(f_mail, 0, SEEK_SET);
	do
	{
		fscanf_s(f_sname, "%d", &(*q).id);
		fgets((*q).surname, 25, f_sname);
		fscanf_s(f_name, "%d", &(*q).id);
		fgets((*q).name, 20, f_name);
		fscanf_s(f_patr, "%d", &(*q).id);
		fgets((*q).patronymic, 25, f_patr);
		fscanf_s(f_sex, "%d", &(*q).id);
		fgets((*q).sex, 4, f_sex);
		fscanf_s(f_phone, "%d", &(*q).id);
		fgets((*q).phone, 14, f_phone);
		fscanf_s(f_mail, "%d", &(*q).id);
		fgets((*q).mail, 30, f_mail);
		fprintf(f_print, "id: %d\nsurname: %s\nname: %s\npatronymic: %s\nsex: %s\nphone: %s\nmail: %s\n", (*q).id, (*q).surname, (*q).name, (*q).patronymic, (*q).sex, (*q).phone, (*q).mail);
		fprintf(f_print, "************************\n");
		c = fgetc(f_mail);
		c = fgetc(f_mail);
		fseek(f_mail, -2, SEEK_CUR);
	} while (c != EOF);
	printf_s("���� ������ �����������");
}
void search_by_name(FILE *f_sname, FILE *f_name, FILE *f_patr, FILE *f_sex, FILE *f_phone, FILE *f_mail, FILE *f_id_b, FILE *f_id_f)
{
	Quest *q, *b;
	int flag1, flag2 = 0;
	char c;
	q = (Quest*)malloc(sizeof(Quest));
	b = (Quest*)malloc(sizeof(Quest));
	printf_s("������� ������ �������� ��������\n");
	printf_s("�������: ");
	fgets((*b).surname, 30, stdin);
	fgets((*b).surname, 30, stdin);
	printf_s("���: ");
	fgets((*b).name, 30, stdin);
	printf_s("��������: ");
	fgets((*b).patronymic, 30, stdin);
	do
	{
		flag1 = 0;
		fscanf_s(f_sname, "%d", &(*q).id);
		fgets((*q).surname, 30, f_sname);
		fscanf_s(f_name, "%d", &(*q).id);
		fgets((*q).name, 30, f_name);
		fscanf_s(f_patr, "%d", &(*q).id);
		fgets((*q).patronymic, 30, f_patr);
		fscanf_s(f_sex, "%d", &(*q).id);
		fgets((*q).sex, 4, f_sex);
		fscanf_s(f_phone, "%d", &(*q).id);
		fgets((*q).phone, 14, f_phone);
		fscanf_s(f_mail, "%d", &(*q).id);
		fgets((*q).mail, 30, f_mail);
		c = fgetc(f_mail);
		c = fgetc(f_mail);
		fseek(f_mail, -2, SEEK_CUR);
		if (strcmp((*q).surname, (*b).surname) == 0)
		{
			flag1++;
		};
		if (strcmp((*q).name, (*b).name) == 0)
		{
			flag1++;
		};
		if (strcmp((*q).patronymic, (*b).patronymic) == 0)
		{
			flag1++;
		};
		if (flag1 == 3)
		{
			flag2++;
			printf_s("������ �������� ��������\n");
			printf_s("id: %d\nsurname: %s\nname: %s\npatronymic: %s\nsex: %s\nphone: %s\nmail: %s\n", (*q).id, (*q).surname, (*q).name, (*q).patronymic, (*q).sex, (*q).phone, (*q).mail);
		}
	} while (c != EOF);
	if (flag2 == 0)
	{
		printf_s("�������� � ������ ������� ��� � ����\n");
	};
	fseek(f_sname, 0, SEEK_SET);
	fseek(f_name, 0, SEEK_SET);
	fseek(f_patr, 0, SEEK_SET);
	fseek(f_sex, 0, SEEK_SET);
	fseek(f_phone, 0, SEEK_SET);
	fseek(f_mail, 0, SEEK_SET);

}

//��� ������
Basic_list * addelem(Basic_list *lst, FILE*f)
{
	Basic_list *temp, *p;
	temp = (Basic_list*)malloc(sizeof(Basic_list));
	p = lst->ptr_b;
	lst->ptr_b = temp;
	fscanf_s(f, "%d", &(*temp).b.id);
	fgets((*temp).b.f.mail, 30, f);
	temp->ptr_b = NULL;
	return(temp);
}
Basic_list * init(FILE*f)
{
	Basic_list *lst;
	lst = (Basic_list*)malloc(sizeof(Basic_list));
	fscanf_s(f, "%d", &(*lst).b.id);
	fgets((*lst).b.f.mail, 30, f);
	lst->ptr_b = NULL;
	return(lst);
}
void listprint(Basic_list *lst, FILE *f)
{
	Basic_list *p;
	p = lst;
	while (p->ptr_b != NULL)
	{
		fprintf_s(f, "%d%s", (*p).b.id, (*p).b.f.mail);
		p = p->ptr_b;
	};
}
Basic_list * form_list(FILE *f)
{
	char c = ' ';
	Basic_list *head, *temp;
	head = init(f);
	temp = head;
	while (c != EOF)
	{
		c = fgetc(f);
		fseek(f, -1, SEEK_CUR);
		temp = addelem(temp, f);
	};
	return(head);
}
Basic_list * delelem(int id, Basic_list *head)
{
	Basic_list *temp, *p;
	if (id == head->b.id)
	{
		temp = head->ptr_b;
		free(head);
		return(temp);
	}
	else
	{
		p = head;
		while (id != p->b.id)
		{
			p = p->ptr_b;
		};
		temp = head;
		while (temp->ptr_b != p)
			temp = temp->ptr_b;
		temp->ptr_b = p->ptr_b;
		delete(p);
		p = temp;
		return(head);
	}

}
void del_file(int id, FILE *f, char *str)
{
	Basic_list *temp;
	temp = (Basic_list*)malloc(sizeof(Basic_list));
	temp = form_list(f);
	fclose(f);
	temp = delelem(id, temp);
	fopen_s(&f, str, "w");
	listprint(temp, f);
	fclose(f);
	fopen_s(&f, str, "r+");

}
