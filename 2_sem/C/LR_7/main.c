#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <windows.h>
#include <string.h>

#define fr 16

typedef struct capital
{
	char name[15];
	double oilPrice; //in $
	double fruitPrice; //in $
	double toBorderBack; //way to Minsk
	double toBorder; //way from Minsk
	double weight;
} capital;

typedef struct truck
{
	double avaiblePlace; //in tonnes
	double oilConsumption; //12 l. per 60 km (20 per 100) //  will be 0.1/30 per s
	double haveOil; //will be 500 l. from start
	unsigned int speed; //speed
	double spent; //spent money
	double spentOnFruits;
	int active; //0 - truck is waiting for a signal to leave
	double toNextPoint; //km to next point
	unsigned int path;
	int onBorder;
	int done; //if 1 - truck driving in the way to Minsk, 0 - truck driving from Minsk
	unsigned int point;
	int visited[7]; //visited capitals
} truck;

typedef struct trucksl
{
	struct trucksl* p;
	struct trucksl* n;
	truck data;
} trucksl;

typedef struct capitalsl
{
	struct capitalsl* p;
	struct capitalsl* n;
	capital data;
}capitalsl;

/*
point:
0 - Minsk
path 1:
1 - Warsaw
2 - Prague
etc...

path 2:
1 - Kiyv
2 - Kishinev
etc...
*/

void writeTTF(FILE*, trucksl*);
void writeCTF(FILE*, capitalsl*);

void readTFF(FILE*, trucksl**);
void readCFF(FILE*, capitalsl**);

void addT(trucksl**, truck); //push_back
void addC(capitalsl**, capital); //push_back

truck* getT(trucksl*, unsigned int);
capital* getC(capitalsl*, unsigned int);

void freeTL(trucksl**); //free
void freeCL(capitalsl**); //free

void ChangePrices(capitalsl**);
void Trading(truck *, capital*);
void MissionCompleted(truck*, capital*);
void PrintTrucks(trucksl*, capitalsl*); 
void PrintFruitPrices(capitalsl*);
void oilRefill(truck*, capital*);

/*
6.2 (29). FruitImport. Белорусская компания импортирует фрукты из ряда
европейских стран. Компания арендует торговые площадки,
находящиеся на двух главных маршрутах: 1) в Варшаве, Праге,
Вене, Милане, Марселе, Барселоне и 2) в Киеве, Кишиневе,
Бухаресте, Софии, Афинах. FruitImport располагает 6 грузовиками,
каждый из которых способен перевезти максимум 25 тонн груза. В
каждой машине едет 2 водителя, таким образом, машина находится
в пути круглосуточно. Средняя скорость – 60 км/ч, среднее время на
пересечение границы – 4 часа. Стоимость бензина и зарплата
водителям – стандартные. В Минске компания сразу реализует
привезенные фрукты оптовику, ее прибыль составляет 5-15% от
выручки. Каждый час, в течение суток, партнеры передают
компании информацию о поставках фруктов (объем (тонн) и цена
партии) на торговых площадках. Разработать программу
оптимального движения грузовиков FruitImport.
Проиллюстрировать движение автомобилей и совершаемые
деловые операции в режиме реального времени.
*/

int main()
{
	{
		FILE* capitalsdata;
		char* pathCapitals = "D:\\BSUIR\\Tapping\\C\\LR_7\\capitalssave.txt";		
		capitalsdata = fopen(pathCapitals, "rb");
		if (!capitalsdata)
		{
			return 1;
		}
		capitalsl* capitals = NULL;
		readCFF(capitalsdata, &capitals);

		fclose(capitalsdata);
		FILE* trucksdata;
		char* pathTrucks = "D:\\BSUIR\\Tapping\\C\\LR_7\\truckssave.txt";
		trucksdata = fopen(pathTrucks, "rb");
		
		if (!trucksdata)
		{
			fclose(capitalsdata);
			return 1;
		}		
		trucksl* trucks = NULL;
		readTFF(trucksdata, &trucks);			
		fclose(trucksdata);

		unsigned long long whenOnBorder[6];
		unsigned long long lastPriceChange = 0;

		int timeBoost = 0;

		double path1price = 0;
		double path2price = 0;

		for (char i = 1; i < 7; i++)
		{
			capital* cap = getC(capitals, i);
			path1price += cap->fruitPrice * cap->weight;
		}

		for (char i = 7; i < 12; i++)
		{
			capital* cap = getC(capitals, i);
			path2price += cap->fruitPrice * cap->weight;
		}


		for (unsigned long long sec = 0; !GetAsyncKeyState(0x1B); sec++) //main cycle
		{
			system("cls");

			if (GetAsyncKeyState(0x54))  // 't' pressed, boost time
			{
				while (GetAsyncKeyState(0x54)) {};

				if (!timeBoost)
				{
					timeBoost = 1;
				}
				else
				{
					timeBoost = 0;
				}
			}

			if (sec - lastPriceChange >= 3600) //changing prices
			{
				ChangePrices(&capitals);
				lastPriceChange = sec;

				path1price = 0;
				path2price = 0;

				capital* cap;

				for (char i = 1; i < 7; i++)
				{
					cap = getC(capitals, i);
					path1price += cap->fruitPrice * cap->weight;
				}

				for (char i = 7; i < 12; i++)
				{
					cap = getC(capitals, i);
					path2price +=cap->fruitPrice * cap->weight;
				}
			}

			if (GetAsyncKeyState(0x31)) // '1' pressed, path 1
			{
				while (GetAsyncKeyState(0x32)) {};
				for (char i = 0; i < 6; i++)
				{
					truck* tr = getT(trucks, i);
					if (!tr->active)
					{
						tr->path = 1;
						tr->active = 1;
						tr->toNextPoint = getC(capitals, 0)->toBorder;
						tr->point = 0;

						for (int j = 0; j < 7; j++)
						{
							tr->visited[j] = 0;
						}

						break;
					}
				}
			}
			if (GetAsyncKeyState(0x32)) //'2' pressed, path 2
			{
				while (GetAsyncKeyState(0x32)) {};
				for (char i = 0; i < 6; i++)
				{
					truck* tr = getT(trucks, i);
					if (!tr->active)
					{
						tr->path = 2;
						tr->active = 1;
						tr->toNextPoint = getC(capitals, 0)->toBorderBack;
						tr->point = 0;

						for (int j = 0; j < 7; j++)
						{
							tr->visited[j] = 0;
						}

						break;
					}
				}
			}
			if (GetAsyncKeyState(0x61)) //'numpad 1' pressed
			{
				while (GetAsyncKeyState(0x61)) {};
				for (char i = 0; i < 6; i++)
				{
					truck* tr = getT(trucks, i);
					if (!tr->active)
					{
						tr->path = 1;
						tr->active = 1;
						tr->toNextPoint = 0;
						tr->point = 6;

						for (int j = 0; j < 7; j++)
						{
							tr->visited[j] = 0;
						}

						break;
					}
				}
			}
			if (GetAsyncKeyState(0x62)) //'numpad 2' pressed
			{
				while (GetAsyncKeyState(0x61)) {};
				for (char i = 0; i < 6; i++)
				{
					truck* tr = getT(trucks, i);
					if (!tr->active)
					{
						tr->path = 2;
						tr->active = 1;
						tr->toNextPoint = 0;
						tr->point = 5;

						for (int j = 0; j < 7; j++)
						{
							tr->visited[j] = 0;
						}

						break;
					}
				}
			}

			if (GetAsyncKeyState(0x43)) //'c' pressed
			{
				while (GetAsyncKeyState(0x43)) {};
				for (char i = 0; i < 6; i++)
				{
					truck* tr = getT(trucks, i);
					tr->avaiblePlace = 25;
					tr->haveOil = 500;
					tr->oilConsumption = 0.003;
					tr->speed = 60; // 1/60 km in s ~ 0,167
					tr->spent = 0;
					tr->active = 0;
					tr->toNextPoint = 0;
					tr->onBorder = 0;
					tr->point = 0;
					tr->done = 0;
					tr->spentOnFruits = 0;
				}
			}

			if (!timeBoost) //prints
			{
				//prices of fruits on pathes
				{
					puts("'esc' - exit\n't' - time boost, depends on computing power\n'h' - an hour ahead\n'1' - send truck on the 1st path\n'2' - send truck on the 2nd path\n'numpad 1' - send truck on the 1st path to Minsk\n'numpad 2' - send truck on the 2nd path to Minsk\n'c' - clear all trucks\n\n");

					printf("Path 1 fruit price: $%.2f\nPath 2 fruit price: $%.2f\n", path1price, path2price);

					if (path1price * 5 < path2price * 6)
					{
						puts("Path 1 is more profitable.");
					}
					else if (path1price * 5 > path2price * 6)
					{
						puts("Path 2 is more profitable.");
					}
					else
					{
						puts("Pathes are equal");
					}

					puts("\n");
				}

				PrintTrucks(trucks, capitals);
				puts("\n\n");
				PrintFruitPrices(capitals);
			}

			for (char i = 0; i < 6; i++)
			{
				truck* tr = getT(trucks, i);

				if (tr->active)
				{
					if (tr->onBorder)
					{
						if ((sec - whenOnBorder[i]) >= 3600 * 4)
						{
							tr->onBorder = 0;
						}
					}
					else //slill driving
					{
						tr->toNextPoint -= (double)tr->speed / 3600;
						tr->haveOil -= tr->oilConsumption;

						if (tr->haveOil <= 100) //instant oil refilling, yep
						{
							oilRefill(tr, (getC(capitals,tr->point + ((tr->path == 1) ? (0) : (6)))));
						}

						if (tr->toNextPoint <= 0) //arrive to some point
						{
							if (tr->done) //to Minsk
							{
								if (!tr->point) //arrived to Minsk
								{
									MissionCompleted(tr, getC(capitals, 0));

									if (!timeBoost)
									{
										Sleep(5000);
									}

									continue;
								}

								if (tr->visited[tr->point])//(tr->visited[tr->point + ((tr->path == 1) ? (0) : (6))]) //have arrived to border (tr->visited[((tr->path == 1) ? (5) : (4))])
								{
									tr->onBorder = 1;
									whenOnBorder[i] = sec; //time when start crossing the border
									tr->point--;
									tr->toNextPoint = getC(capitals, tr->point + ((tr->path == 1) ? (0) : (6)))->toBorder;
								}
								else //have arrived to capital
								{
									Trading(tr, getC(capitals, tr->point + ((tr->path == 1) ? (0) : (6))));

									if (!timeBoost)
									{
										Sleep(2000);
									}
									tr->visited[tr->point] = 1;
									tr->toNextPoint = getC(capitals, tr->point + ((tr->path == 1) ? (0) : (6)))->toBorderBack;
								}
							}
							else //from Minsk
							{
								if (tr->point == ((tr->path == 1) ? (6) : (5))) //end of the path from Minsk, driving back
								{
									Trading(tr, getC(capitals, tr->point + ((tr->path == 1) ? (0) : (6))));

									if (!timeBoost)
									{
										Sleep(2000);
									}

									tr->done = 1;
									tr->visited[tr->point] = 1;
									tr->toNextPoint = getC(capitals, tr->point + ((tr->path == 1) ? (0) : (6)))->toBorderBack;
								}
								else //have arrived to border
								{
									tr->point++;
									tr->toNextPoint = getC(capitals, tr->point + ((tr->path == 1) ? (0) : (6)))->toBorder +
										getC(capitals, tr->point + ((tr->path == 1) ? (0) : (6)))->toBorderBack;

									tr->onBorder = 1;
									whenOnBorder[i] = sec; //time when start crossing the border
								}
							}
						}
					}
				}
			}

			if (GetAsyncKeyState(0x48)) // 'h' pressed
			{
				while (GetAsyncKeyState(0x48)) {};

				for (char i = 0; i < 6; i++)
				{
					truck* tr = getT(trucks, i);

					if ((tr->active) && (!tr->onBorder))
					{
						if ((tr->toNextPoint - tr->speed) > 0) //if it ok and in an hour he will still ride
						{
							tr->toNextPoint -= tr->speed;

							if ((tr->haveOil -= tr->oilConsumption * 3600) < 100) //instant oil refilling, yep
							{
								if (!tr->point)
								{
									oilRefill(tr, getC(capitals, 0));
								}
								else
								{
									oilRefill(tr, getC(capitals, tr->point + ((tr->path == 1) ? (0) : (6))));
								}
							}
						}
						else
						{
							double secToPoint = tr->toNextPoint / (double)tr->speed * 3600;

							if (tr->done) //path to Minsk
							{
								if (!tr->point)
								{
									MissionCompleted(tr, getC(capitals, 0));

									if (!timeBoost)
									{
										Sleep(2000);
									}

									continue;
								}
								else if (tr->visited[tr->point]) //have arrived to border
								{
									tr->onBorder = 1;
									whenOnBorder[i] = sec + secToPoint; //time when start crossing the border
									tr->point--;
									tr->toNextPoint = getC(capitals, tr->point + ((tr->path == 1) ? (0) : (6)))->toBorder;
								}
								else //have arrived to capital
								{
									Trading(tr, getC(capitals, tr->point + ((tr->path == 1) ? (0) : (6))));

									if (!timeBoost)
									{
										Sleep(2000);
									}

									tr->visited[tr->point] = 1;
									tr->toNextPoint = (getC(capitals, tr->point + ((tr->path == 1) ? (0) : (6)))->toBorderBack - (sec + 3600 - secToPoint) * (tr->speed / 3600));
								}
							}
							else //path from Minsk
							{
								if (tr->point == ((tr->path == 1) ? (6) : (5))) //end of the path from Minsk, driving back
								{
									Trading(tr, getC(capitals, tr->point + ((tr->path == 1) ? (0) : (6))));

									if (!timeBoost)
									{
										Sleep(5000);
									}

									tr->visited[tr->point] = 1;
									tr->done = 1;
									tr->toNextPoint = (getC(capitals, tr->point + ((tr->path == 1) ? (0) : (6)))->toBorderBack - (sec + 3600 - secToPoint) * (tr->speed / 3600));
								}
								else //have arrived to border
								{
									tr->point++;
									tr->toNextPoint = (getC(capitals, tr->point + ((tr->path == 1) ? (0) : (6)))->toBorder +
										getC(capitals, tr->point + ((tr->path == 1) ? (0) : (6)))->toBorderBack);

									tr->onBorder = 1;
									whenOnBorder[i] = sec + secToPoint; //time when start crossing the border
								}
							}

							if ((tr->haveOil -= tr->oilConsumption * secToPoint) < 100) //instant oil refilling, yep
							{
								oilRefill(tr, (getC(capitals, tr->point + ((tr->path == 1) ? (0) : (6)))));
							}

						}
					}
					else if (tr->onBorder)
					{
						double deltatime = ((sec - whenOnBorder[i]) - ((double)3600 * 4));

						if (deltatime >= 0)
						{
							tr->onBorder = 0;
							tr->toNextPoint -= (deltatime * ((double)tr->speed / 3600));
						}
					}
				}

				sec += 3600;
			}

			if (!timeBoost)
			{
				Sleep(850); //~sec, taking into account time spent above
			}
		}

		FILE* truckssave = fopen(pathTrucks, "wb");
		FILE* capitalssave = fopen(pathCapitals, "wb");

		writeTTF(truckssave, trucks);
		writeCTF(capitalssave, capitals);

		fclose(truckssave);
		fclose(capitalssave);

		freeTL(&trucks);
		freeCL(&capitals);
	}	

	puts("\n\nany key\n\n");
	return 0;
}

void writeTTF(FILE* file, trucksl* trucks)
{
	trucksl* i = trucks;
	int counter = 0;
	for (; i; i = i->n)
	{
		fprintf(file, "//%d\n", counter++);
		fprintf(file, "%d\n", i->data.path);		
		fprintf(file, "%f\n", i->data.avaiblePlace);
		fprintf(file, "%lf\n", i->data.haveOil);
		fprintf(file, "%lf\n", i->data.oilConsumption);
		fprintf(file, "%u\n", i->data.speed);
		fprintf(file, "%lf\n", i->data.spent);
		fprintf(file, "%d\n", i->data.active);
		fprintf(file, "%lf\n", i->data.toNextPoint);
		fprintf(file, "%d\n", i->data.onBorder);
		fprintf(file, "%u\n", i->data.point);
		fprintf(file, "%d\n", i->data.done);
		fprintf(file, "%lf\n", i->data.spentOnFruits);


		if (counter < 6)
		{
			fprintf(file, "\n\n");
		}
	}
}
void writeCTF(FILE* file, capitalsl* capitals)
{
	capitalsl* i = capitals;
	int counter = 0;

	for (; i; i = i->n)
	{
		fprintf(file, "//%d\n", counter++);
		fprintf(file, "%lf\n", i->data.fruitPrice);
		fprintf(file, "%lf\n", i->data.oilPrice);
		fprintf(file, "%lf\n", i->data.toBorderBack);
		fprintf(file, "%lf\n", i->data.toBorder);
		fprintf(file, "%lf\n", i->data.weight);
		fprintf(file, "%s", i->data.name);

		if (counter < 12)
		{
			fprintf(file, "\n\n");
		}
	}
}

void ChangePrices(capitalsl** capitals)
{
	capital* cap = getC(*capitals, 0);
	cap->fruitPrice = 1.75 * (120. - (double)(rand() % 41)) / (double)100;

	for (char i = 1; i < 12; i++)
	{
		cap = getC(*capitals, i);
		cap->fruitPrice = 1.5 * (120. - (double)(rand() % 41)) / (double)100;
		cap->weight = 3 * (((150.0 - (double)(rand() % 51)) / 100.0) * 1000);
	}
}

void PrintFruitPrices(capitalsl* capitals)
{
	printf("Minsk: $%.2f per kg\n\n", getC(capitals, 0)->fruitPrice);
	capital* cap;
	puts("path 1:");
	for (char i = 1; i < 7; i++)
	{
		cap = getC(capitals, i);
		printf("%s: have %.2f kg, $%.2f per kg\n", cap->name, cap->weight, cap->fruitPrice);
	}

	puts("\npath 2:");
	for (char i = 7; i < 12; i++)
	{
		cap = getC(capitals, i);
		printf("%s: have %.2f kg, $%.2f per kg\n", cap->name, cap->weight, cap->fruitPrice);
	}
}

void Trading(truck* truck, capital* cap)
{
	int kgs = 3 * (((150.0 - (double)(rand() % 51))/100.0)*1000);

	if (truck->avaiblePlace*1000 - (double)kgs < 0)
	{
		kgs -= (truck->avaiblePlace*1000);
	}

	truck->avaiblePlace -= kgs / 1000.0;
	truck->spent += kgs * cap->fruitPrice;
	truck->spentOnFruits += kgs * cap->fruitPrice;

	printf("\n\nTruck bought %.2f tonnes of fruits in %s", kgs / 1000.0, cap->name);
}

void MissionCompleted(truck* tr, capital* Minsk)
{
	double cash = Minsk->fruitPrice * ((25.0 - tr->avaiblePlace) * 1000);
	printf("Truck from path %d has arrived.\n Revenue is $%f - $%f", tr->path, cash * 0.1, cash * 0.15); //%10-15
	
	tr->avaiblePlace = 25;
	tr->haveOil = 500;
	tr->oilConsumption = 0.003;
	tr->speed = 60; // 1/60 km in s ~ 0,167
	tr->spent = 0;
	tr->active = 0;
	tr->toNextPoint = 0;
	tr->onBorder = 0;
	tr->point = 0;
	tr->done = 0;
	tr->spentOnFruits = 0;
}

void PrintTrucks(trucksl* trucks, capitalsl* capitals)
{
	puts("# N | path | state | next p. | oil | place | money spent | way | point | where | visited #\n");
	for (char i = 0; i < 6; i++)
	{
		truck* tr = getT(trucks, i);
		if (tr->active)
		{
			printf("# %d | %u | %s | %.2f | %.2f | %.2f | $%.2f | %s | %u | %s | %s #\n",
				i + 1,
				tr->path,
				(tr->onBorder) ? ("on border") : ("driving"),
				tr->toNextPoint,
				tr->haveOil,
				tr->avaiblePlace,
				tr->spent,
				(tr->done)?("to Minsk"):("from Minsk"),
				tr->point,
				getC(capitals, (tr->point)?(tr->point + ((tr->path == 1) ? (0) : (6))):(0))->name,
				(tr->visited[tr->point])?("yep"):("nope"));
		}
	}
}

void oilRefill(truck* truck, capital* cap)
{
	(*truck).haveOil += 400;
	(*truck).spent += cap->oilPrice * 400;
}

void readTFF(FILE* file, trucksl** trucks)
{
	char buf[fr - 1];

	if (!*trucks)
	{
		*trucks = (trucksl*)malloc(sizeof(trucksl));
		(*trucks)->n = NULL;
		(*trucks)->p = NULL;
	}

	trucksl* i = *trucks;

	for (; !feof(file); i = i->n)
	{
		fgets(buf, fr, file);

		fgets(buf, fr, file);
		sscanf(buf, "%d", &i->data.path);

		fgets(buf, fr, file);
		sscanf(buf, "%lf", &i->data.avaiblePlace);

		fgets(buf, fr, file);
		sscanf(buf, "%lf", &i->data.haveOil);

		fgets(buf, fr, file);
		sscanf(buf, "%lf", &i->data.oilConsumption);

		fgets(buf, fr, file);
		sscanf(buf, "%u", &i->data.speed);

		fgets(buf, fr, file);
		sscanf(buf, "%lf", &i->data.spent);

		fgets(buf, fr, file);
		sscanf(buf, "%d", &i->data.active);

		fgets(buf, fr, file);
		sscanf(buf, "%lf", &i->data.toNextPoint);

		fgets(buf, fr, file);
		sscanf(buf, "%d", &i->data.onBorder);

		fgets(buf, fr, file);
		sscanf(buf, "%u", &i->data.point);

		fgets(buf, fr, file);
		sscanf(buf, "%d", &i->data.done);

		fgets(buf, fr, file);
		sscanf(buf, "%lf", &i->data.spentOnFruits);

		fgets(buf, fr, file);

		{	int ord = 0;
			for (int j = 0; j < strlen(buf); j++)
			{
				if (buf[j] == '0' || buf[j] == '1')
				{
					i->data.visited[ord++] = buf[j] - '0';
					if (ord == 7)
					{
						break;
					}
				}
			}

			for (; ord < 7; ord++)
			{
				i->data.visited[ord] = 0;
			}
		}

		if (!i->n)
		{
			i->n = (trucksl*)malloc(sizeof(trucksl));
			i->n->n = NULL;
			i->n->p = i;
		}

		fgets(buf, fr, file);
	}

	i = i->p;
	free(i->n);
	i->n = NULL;
}
void readCFF(FILE* file, capitalsl** capitals)
{
	char buf[fr-1];

	if (!*capitals)
	{
		*capitals = (capitalsl*)malloc(sizeof(capitalsl));
		(*capitals)->n = NULL;
		(*capitals)->p = NULL;
	}

	capitalsl* i = *capitals;

	for (; !feof(file); i = i->n)
	{
		fgets(buf, fr, file);

		fgets(buf, fr, file);
		sscanf(buf, "%lf", &i->data.fruitPrice);

		fgets(buf, fr, file);
		sscanf(buf, "%lf", &i->data.oilPrice);

		fgets(buf, fr, file);
		sscanf(buf, "%lf", &i->data.toBorderBack);

		fgets(buf, fr, file);
		sscanf(buf, "%lf", &i->data.toBorder);		

		fgets(buf, fr, file);
		sscanf(buf, "%lf", &i->data.weight);

		fgets(buf, fr, file);
		sscanf(buf, "%s", i->data.name);

		if (!i->n)
		{
			i->n = (capitalsl*)malloc(sizeof(capitalsl));
			i->n->n = NULL;
			i->n->p = i;
		}

		fgets(buf, fr, file);
	}

	i = i->p;
	free(i->n);
	i->n = NULL;
}

truck* getT(trucksl* trucks, unsigned int index)
{
	trucksl* i;
	unsigned int count = 0;

	for (i = trucks; i; i = i->n, count++)
	{
		if (count == index)
		{
			return &i->data;
		}
	}

	return NULL;
}
capital* getC(capitalsl* capitals, unsigned int index)
{
	capitalsl* i;
	unsigned int count = 0;

	for (i = capitals; i; i = i->n, count++)
	{
		if (count == index)
		{
			return &i->data;
		}
	}

	return NULL;
}

void freeTL(trucksl** trucks)
{
	if (!(*trucks)) //size == 0
	{
		return;
	}
	else if (!(*trucks)->n) //size == 1
	{
		free(*trucks);
		*trucks = NULL;
		return;
	}


	trucksl* i = *trucks;
	trucksl* temp = i;
	i = i->n;

	for (; i; i = i->n)
	{
		free(temp);
		temp = i;
	}

	free(temp);

	*trucks = NULL;
}
void freeCL(capitalsl** capitals)
{
	if (!(*capitals)) //size == 0
	{
		return;
	}
	else if (!(*capitals)->n) //size == 1
	{
		free(*capitals);
		*capitals = NULL;
		return;
	}


	capitalsl* i = *capitals;
	capitalsl* temp = i;
	i = i->n;

	for (; i; i = i->n)
	{
		free(temp);
		temp = i;
	}

	free(temp);

	*capitals = NULL;
}