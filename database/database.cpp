// database.cpp: определяет точку входа для консольного приложения.
//
#include "stdafx.h"
#include <stdio.h> 
#include <conio.h> 
#include <string.h> 
#include <Windows.h> 
#include <cmath> 
#include <locale.h>

//Описание структур 
//Запись, содержащая все данные о человеке
typedef struct questionnaire
{
	int id;
	char surname[25], name[20], patronymic[25], sex[4], phone[14], mail[30];
} Quest;
// Объединение, чтобы работать сразу со всеми полями при id
typedef union field
{
	char surname[25], name[20], patronymic[25], sex[4], phone[14], mail[30];
} Field;
//Основная структура для работы с файлами
typedef struct basic
{
	int id;
	Field f;
} Basic;
//Структура для стека из базовой структуры
typedef struct basic_list
{
	Basic b;
	struct basic_list *ptr_b;
} Basic_list;

//Объявление функций
//Основные функции для работы с базой
//Проверка на присутствие в базе
int check_id(FILE *, FILE *);
//Поиск по id
void search_by_id(FILE *, FILE *, FILE *, FILE *, FILE *, FILE *, FILE *, FILE *);
//Удаление по id
void del_by_id(FILE *, FILE *, FILE *, FILE *, FILE *, FILE *, FILE *, FILE *);
//Добавление нового элемента
void add(FILE *, FILE *, FILE *, FILE *, FILE *, FILE *, FILE *, FILE *);
//Вывод на печать всей базы
void print_all(FILE *, FILE *, FILE *, FILE *, FILE *, FILE *, FILE *, FILE *, FILE *);
//Поиск по ФИО
void search_by_name(FILE *, FILE *, FILE *, FILE *, FILE *, FILE *, FILE *, FILE *);

//Вспомогательные функции
//Для списка
//Добавление нового элемента
Basic_list * addelem(Basic_list *, FILE *);
//Инициализация списка
Basic_list * init(FILE *);
//Печать списка
void listprint(Basic_list *, FILE *);
//Формирование списка
Basic_list * form_list(FILE *);
//Удаление элемента из файла
void del_file(int, FILE *, char *);
//Удаление элемента из списка
Basic_list * delelem(int, Basic_list *);

int main()
{
	//Подключаем русский язык 
	/*SetConsoleCP(1251);
	SetConsoleOutputCP(1251);*/
	setlocale(LC_ALL, "Rus");
	//Объявляем переменные 
	FILE *f_sname, *f_name, *f_patr, *f_sex, *f_phone, *f_mail, *f_id_b, *f_id_f, *f_print;
	int i = 0;

	//Открываем файлы 
	fopen_s(&f_sname, "surname.txt", "r+");
	fopen_s(&f_name, "name.txt", "r+");
	fopen_s(&f_patr, "patronymic.txt", "r+");
	fopen_s(&f_sex, "sex.txt", "r+");
	fopen_s(&f_phone, "phone.txt", "r+");
	fopen_s(&f_mail, "mail.txt", "r+");
	fopen_s(&f_id_b, "id_busy.txt", "r+");
	fopen_s(&f_id_f, "id_free.txt", "r+");
	fopen_s(&f_print, "print_all.txt", "w");

	//Проверка открытия файлов 
	if (f_sname == NULL) {
		printf("Ошибка открытия файла surname.txt \n");
	}
	else
	{
		printf("Файл surname.txt открыт \n");
	};
	if (f_name == NULL) {
		printf("Ошибка открытия файла name.txt \n");
	}
	else
	{
		printf("Файл name.txt открыт \n");
	};
	if (f_patr == NULL) {
		printf("Ошибка открытия файла patronymic.txt \n");
	}
	else
	{
		printf("Файл patronymic.txt открыт \n");
	};
	if (f_sex == NULL) {
		printf("Ошибка открытия файла sex.txt \n");
	}
	else
	{
		printf("Файл sex.txt открыт \n");
	};
	if (f_phone == NULL) {
		printf("Ошибка открытия файла phone.txt \n");
	}
	else
	{
		printf("Файл phone.txt открыт \n");
	};
	if (f_mail == NULL) {
		printf("Ошибка открытия файла mail.txt \n");
	}
	else
	{
		printf("Файл mail.txt открыт \n");
	};
	if (f_id_b == NULL) {
		printf("Ошибка открытия файла id_busy.txt \n");
	}
	else
	{
		printf("Файл id_busy.txt открыт \n");
	};
	if (f_id_f == NULL) {
		printf("Ошибка открытия файла id_free.txt \n");
	}
	else
	{
		printf("Файл id_free.txt открыт \n");
	};
	if (f_print == NULL) {
		printf("Ошибка открытия файла print_all.txt \n");
	}
	else
	{
		printf("Файл print_all.txt открыт \n");
	};

	printf_s("\n");
	printf_s("База студентов группы 13558/2\n");

	do
	{
		printf_s("\n");
		printf_s("Выберите действие:\n1 Проверить есть ли этот id в базе\n2 Вывести на печать данные по id\n3 Удаление данных по id\n4 Найти студента по ФИО \n5 Добавить новый элемент\n6 Вывести на печать всю базу\n7 Завершить сеанс\n");
		printf_s("Укажите код выбранного действия:");
		scanf_s("%i", &i);
		printf_s("\n");
		switch (i) {
		case 1:
		{
			if (check_id(f_id_b, f_id_f) == 0)
			{
				printf_s("Этого id в базе нет");
			}
			else
			{
				printf_s("Этот id в базе есть\n");
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
			printf_s("Введен неверный код действия\n");
		};
		printf_s("\n");
	} while (i != 7);

	//Закрываем файлы 
	fclose(f_sname);
	printf("Файл surname.txt закрыт \n");
	fclose(f_name);
	printf("Файл name.txt закрыт \n");
	fclose(f_patr);
	printf("Файл patronymic.txt закрыт \n");
	fclose(f_sex);
	printf("Файл sex.txt закрыт \n");
	fclose(f_phone);
	printf("Файл phone.txt закрыт \n");
	fclose(f_mail);
	printf("Файл mail.txt закрыт \n");
	fclose(f_id_b);
	printf("Файл id_busy.txt закрыт \n");
	fclose(f_id_f);
	printf("Файл id_free.txt закрыт \n");
	fclose(f_print);
	printf("Файл print_all.txt закрыт \n");
	return 0;
}

//Реализация функций
//Для базы
int check_id(FILE *f_id_b, FILE *f_id_f)
{
	int flag = 1, id = 0, i = 0;
	char c;
	printf_s("Введите id:");
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
		printf_s("Этого id в базе нет");
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
		printf_s("Данные искомого студента\n");
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
		printf_s("Этого id в базе нет");
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
		printf_s("Данные удалены из базы\n");
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
	printf_s("Введите данные студента\n");
	printf_s("Фамилия: ");
	fgets((*q).f.surname, 25, stdin);
	fgets((*q).f.surname, 25, stdin);
	fseek(f_sname, 0, SEEK_END);
	fprintf(f_sname, "%d %s", (*q).id, (*q).f.surname);
	printf_s("Имя: ");
	fgets((*q).f.name, 20, stdin);
	fseek(f_name, 0, SEEK_END);
	fprintf(f_name, "%d %s", (*q).id, (*q).f.name);
	printf_s("Отчество: ");
	fgets((*q).f.patronymic, 25, stdin);
	fseek(f_patr, 0, SEEK_END);
	fprintf(f_patr, "%d %s", (*q).id, (*q).f.patronymic);
	printf_s("Пол: ");
	fgets((*q).f.sex, 4, stdin);
	fseek(f_sex, 0, SEEK_END);
	fprintf(f_sex, "%d %s", (*q).id, (*q).f.sex);
	printf_s("Телефон: ");
	fgets((*q).f.phone, 14, stdin);
	fseek(f_phone, 0, SEEK_END);
	fprintf(f_phone, "%d %s", (*q).id, (*q).f.phone);
	printf_s("E-mail: ");
	fgets((*q).f.mail, 30, stdin);
	fseek(f_mail, 0, SEEK_END);
	fprintf(f_mail, "%d %s", (*q).id, (*q).f.mail);
	printf_s("Запись занесена в базу\nПрисвоен id: %d", (*q).id);
	//Закрываем файлы 
	fclose(f_sname);
	fclose(f_name);
	fclose(f_patr);
	fclose(f_sex);
	fclose(f_phone);
	fclose(f_mail);
	fclose(f_id_b);
	fclose(f_id_f);
	//Открываем файлы 
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
	fprintf(f_print, "База данных студентов\n");
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
	printf_s("База данных распечатана");
}
void search_by_name(FILE *f_sname, FILE *f_name, FILE *f_patr, FILE *f_sex, FILE *f_phone, FILE *f_mail, FILE *f_id_b, FILE *f_id_f)
{
	Quest *q, *b;
	int flag1, flag2 = 0;
	char c;
	q = (Quest*)malloc(sizeof(Quest));
	b = (Quest*)malloc(sizeof(Quest));
	printf_s("Введите данные искомого студента\n");
	printf_s("Фамилия: ");
	fgets((*b).surname, 30, stdin);
	fgets((*b).surname, 30, stdin);
	printf_s("Имя: ");
	fgets((*b).name, 30, stdin);
	printf_s("Отчество: ");
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
			printf_s("Данные искомого студента\n");
			printf_s("id: %d\nsurname: %s\nname: %s\npatronymic: %s\nsex: %s\nphone: %s\nmail: %s\n", (*q).id, (*q).surname, (*q).name, (*q).patronymic, (*q).sex, (*q).phone, (*q).mail);
		}
	} while (c != EOF);
	if (flag2 == 0)
	{
		printf_s("Студента с такими данными нет в базе\n");
	};
	fseek(f_sname, 0, SEEK_SET);
	fseek(f_name, 0, SEEK_SET);
	fseek(f_patr, 0, SEEK_SET);
	fseek(f_sex, 0, SEEK_SET);
	fseek(f_phone, 0, SEEK_SET);
	fseek(f_mail, 0, SEEK_SET);

}

//Для списка
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
