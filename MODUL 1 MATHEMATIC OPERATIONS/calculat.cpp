#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	int n = atoi(argv[1]);
	int m = atoi(argv[3]);
	char p[2];
	
	if(argc == 4 && strcmp(argv[1], "sum") != 0 && strcmp(argv[1], "avg") != 0 && strcmp(argv[2], "pangkat") != 0)
	{
		p[0] = argv[2][0];
		if(p[0] == '+')
		{
			printf("%i",n + m);	
			
		}else if(p[0] == '-' )
		{
			printf("%i",n - m);
			
		}else if(p[0] == '*' )
		{
			printf("%i",n * m);
			
		}else if(p[0] == '/' )
		{
			if(m == 0){
				printf("cant devide by 0\n");
			}else{
				printf("%i",n/m);
			}
			
		}else if(p[0] == '%' )
		{
			if(n == 0 && m == 0)
			{
				printf("0");
			}else
			{	
				int b = n % m;	
				int i;
				for(i=0; n >= 0; i++)
				{
					n = n-m;
				}	
				printf("hasilnya %i, sisanya %i", i-1, b);
			}
		}
//		else if(p[0] == 'p' )
//		{
//			if(n == 0)
//			{
//				printf("0");
//			}
//			else
//			{
//				int z = 1;
//				for(int i= 0; i < m; i++){
//					z = z * n;
//				}
//				printf("%i", z);
//			}
//		}
		else if(strcmp(argv[2], "div") == 0 )
		{
			int i;
			for(i=0; n > 0; i++)
			{
				n = n-m;				
			}	
			printf("hasilnya %i", i-1);
		}else if(strcmp(argv[2], "mod") == 0 )
		{
			printf("%i",n % m);
		}
		
	else if (strcmp(argv[2],"log") == 0 ){
	double log_arg3 = log(atoi(argv[3]));
	double log_arg1 = log(atoi(argv[1]));
	double result = (log_arg3)/(log_arg1);
	printf ("%s log10(%s) = %lf\n", argv[1], argv[3], result);
}
		else{
			printf("operasi tidak diketahui");
		}
	}
	else if(argc == 3 && strcmp(argv[1], "sum") != 0 && strcmp(argv[1], "avg") != 0  && strcmp(argv[2], "pangkat") != 0)
	{
		if(strcmp(argv[1], "log") == 0 )
		{
			double hasil = (double)log10(atoi(argv[2]));
			printf("log %i = %.2lf\n", atoi(argv[2]), hasil);
		}else if(strcmp(argv[1], "akar") == 0)
		{
			double hasil = sqrt(atoi(argv[2]));		
			printf("Akar kuadrat dari %lld adalah %.2lf\n", atoi(argv[2]), hasil);	
		}else if(strcmp(argv[1], "sin") == 0)
		{
			int n = atoi(argv[2]);
       		double hasil = sin(n * M_PI / 180.0);
        	printf("Sin dari %i derajat = %.2lf\n", n, hasil);
		}else if(strcmp(argv[1], "cos") == 0)
		{
			int n = atoi(argv[2]);
       		double hasil = cos(n * M_PI / 180.0);
        	printf("Cos dari %i derajat = %.2lf\n", n, hasil); 	
		}
	else if  (strcmp(argv[1], "tan") == 0) {
        int n = atoi(argv[2]);
        if (n % 180 == 90) {
            printf("Tangent dari sudut %i derajat tidak terdefinisi.\n", n);
        } else if (n % 180 == 0) {
            printf("Tan dari %i derajat = %.2lf\n", n, 0.0);
        } else {
            double hasil = tan(n * M_PI / 180.0);
            printf("Tan dari %i derajat = %.2lf\n", n, hasil);
        }	
				
		}else if(strcmp(argv[1], "ln") == 0)
		{
			double i = atoi(argv[2]);
       		 if (i <= 0)
			{
            	printf("Logaritma natural tidak terdefinisikan untuk nilai non-positif atau nol\n");
       		} else
			{
            	double hasilLn = log(i);
            	printf("Ln dari %.2lf = %.2lf\n", i, hasilLn);
      		}
		}else if(strcmp(argv[1], "factorial") == 0)
		{
			int f = 1;
			if(atoi(argv[2]) < 0)
			{
				printf("Faktorial tidak terdefinisikan untuk bilangan negatif");
			}else
			{
				for(int i = 0; i < atoi(argv[2]); i++)
				{
					f *= (i + 1);	
				}
				if (atoi (argv[2]) == 0){
				printf("tidak terdefinisi");
				}
				else{
				printf("!%i = %i\n", atoi(argv[2]), f);
				}
				
			}
			
		}
	}
	else if(strcmp(argv[1], "sum") == 0)
	{
		int hasil = 0;
        for (int i = 2; i < argc; i++) {
            hasil += atoi(argv[i]);
        }
        printf("Jumlah dari ");
        for(int i = 2; i < argc; i++){
            printf("%i", atoi(argv[i]));
            if(i < argc - 1){
                printf(" + ");
            }
        }
        printf(" = %lld\n", hasil);
	}else if(strcmp(argv[1], "avg") == 0)
	{
    	int j = 0;	
    	for(int i = 2; i < argc; i++){
    		j += atoi(argv[i]);
		}
    	double r = (double)j / (argc - 2);
    	printf("Rata rata = %.2lf\n", r);
    	
	}
	else if(strcmp(argv[2], "pangkat") == 0)
	{
			if(n == 0)
			{
				printf("0");
			}
			else
			{
				int z = 1;
				for(int i= 0; i < m; i++){
					z = z * n;
				}
				printf("%i", z);
			}
		}
	return 0;
}
