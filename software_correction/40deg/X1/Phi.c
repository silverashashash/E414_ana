#include <stdio.h>
#include <math.h>

main()
{
  /* p = A + B*y + C*y*t + D*y*t^2 + E*y*t^3                       */
  /* A=y0                                                          */
  /* B=(y|y)                                                       */
  /* C=(y|y,t)                                                     */
  /* D=(y|y,t*t)                                                   */
  /* E=(y|y,t*t*t)                                                 */
  /* a(n)=1, b(n)=y(n), c(n)=y(n)*t(n), d(n)=y(n)*t(n)^2,          */
  /* e(n)=y(n)*t(n)^3                                              */
  /* f(A,B,C,D) = sigma(n)[p(n)-y(y(n),t(n))]^2                    */
  /*                                                               */
  /* df/dA/2 = sigma(n)[a(n)^2]*A + sigma(n)[a(n)*b(n)]*B          */
  /*           + sigma(n)[a(n)*c(n)]*C + sigma(n)[a(n)*d(n)]*D     */
  /*           + sigma(n)[a(n)*e(n)]*E + sigma(n)[a(n)*p(n)]       */
  /* df/dB/2 = sigma(n)[a(n)*b(n)]*A + sigma(n)[b(n)^2]*B          */
  /*           + sigma(n)[b(n)*c(n)]*C + sigma(n)[b(n)*d(n)]*D     */
  /*           + sigma(n)[b(n)*e(n)]*E +sigma(n)[b(n)*p(n)]        */
  /* df/dC/2 = sigma(n)[a(n)*c(n)]*A + sigma(n)[b(n)*c(n)]*B       */
  /*           + sigma(n)[c(n)^2]*C + sigma(n)[c(n)*d(n)]*D        */
  /*           + sigma(n)[c(n)*e(n)]*E + sigma(n)[c(n)*p(n)]       */
  /* df/dD/2 = sigma(n)[a(n)*d(n)]*A + sigma(n)[b(n)*d(n)]*B       */
  /*           + sigma(n)[c(n)*d(n)]*C + sigma(n)[d(n)^2]*D        */
  /*           + sigma(n)[d(n)*e(n)]*E + sigma(n)[d(n)*p(n)]       */
  /* df/dE/2 = sigma(n)[a(n)*e(n)]*A + sigma(n)[b(n)*e(n)]*B       */
  /*           + sigma(n)[c(n)*e(n)]*C + sigma(n)[d(n)*e(n)]*D     */
  /*           + sigma(n)[e(n)^2]*E + sigma(n)[e(n)*p(n)]          */
  /* df/dA=0, df/dB=0, df/dC=0, df/dD=0, df/dE=0                   */
  /*                                                               */
  /*  { M11 M12 M13 M14 M15 }{A} = {a} ---(1)                      */
  /*  { M21 M22 M23 M24 M25 }{B} = {b} ---(2)                      */
  /*  { M31 M32 M33 M34 M35 }{C} = {c} ---(3)                      */
  /*  { M41 M42 M43 M44 M45 }{D} = {d} ---(4)                      */
  /*  { M51 M52 M53 M54 M55 }{E} = {e} ---(5)                      */
  /*                                                               */
  /*  (1)/M11                                                      */
  /*  (2)-(1)'*M21                                                 */
  /*  (3)-(1)'*M31                                                 */
  /*  (4)-(1)'*M41                                                 */
  /*  (5)-(1)'*M51                                                 */
  /*  (2)/M22                                                      */
  /*  (3)-(2)'*M32                                                 */
  /*  (4)-(2)'*M42                                                 */
  /*  (5)-(2)'*M52                                                 */
  /*  (3)/M33                                                      */
  /*  (4)-(3)'*M43                                                 */
  /*  (5)-(3)'*M53                                                 */
  /*  (4)/M44                                                      */
  /*  (5)-(4)'*M54                                                 */
  /*  (5)/M55                                                      */
  /*  (4)-(5)'*M45                                                 */
  /*  (3)-(5)'*M35                                                 */
  /*  (2)-(5)'*M25                                                 */
  /*  (1)-(5)'*M15                                                 */
  /*  (3)-(4)'*M34                                                 */
  /*  (2)-(4)'*M24                                                 */
  /*  (1)-(4)'*M14                                                 */
  /*  (2)-(3)'*M13                                                 */
  /*  (1)-(3)'*M13                                                 */
  /*  (1)-(2)'*M12                                                 */

  int i,j,k;
  int ff;
  float t,x,p;
  float a1,a2,a3,a4,a5,a6,a7,a8,a9;
  float uu;
  float ca1,ca2,ca3,ca4,ca5,ca6,ca7,ca8,ca9;
  static float ms[9][9]={
    {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},
    {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},
    {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},
    {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},
    {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},
    {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},
    {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},
    {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},
    {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},
    };
  static float sp[9]={0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};
FILE *fp;
  fp = fopen("Y1fp_data.dat","r");
  while((ff=fscanf(fp,"%f %f %f",&p,&t,&x)) != EOF){ // phi, y1, x
    a1=1;
    a2=x;
    a3=x*x;
    a4=t;
    a5=x*t;
    a6=x*x*t;
    a7=t*t;
    a8=t*t*x;
    a9=t*t*x*x;

    ms[0][0]=ms[0][0]+a1*a1;
    ms[0][1]=ms[0][1]+a1*a2;
    ms[0][2]=ms[0][2]+a1*a3;
    ms[0][3]=ms[0][3]+a1*a4;
    ms[0][4]=ms[0][4]+a1*a5;
    ms[0][5]=ms[0][5]+a1*a6;
    ms[0][6]=ms[0][6]+a1*a7;
    ms[0][7]=ms[0][7]+a1*a8;
    ms[0][8]=ms[0][8]+a1*a9;

    ms[1][0]=ms[1][0]+a2*a1;
    ms[1][1]=ms[1][1]+a2*a2;
    ms[1][2]=ms[1][2]+a2*a3;
    ms[1][3]=ms[1][3]+a2*a4;
    ms[1][4]=ms[1][4]+a2*a5;
    ms[1][5]=ms[1][5]+a2*a6;
    ms[1][6]=ms[1][6]+a2*a7;
    ms[1][7]=ms[1][7]+a2*a8;
    ms[1][8]=ms[1][8]+a2*a9;

    ms[2][0]=ms[2][0]+a3*a1;
    ms[2][1]=ms[2][1]+a3*a2;
    ms[2][2]=ms[2][2]+a3*a3;
    ms[2][3]=ms[2][3]+a3*a4;
    ms[2][4]=ms[2][4]+a3*a5;
    ms[2][5]=ms[2][5]+a3*a6;
    ms[2][6]=ms[2][6]+a3*a7;
    ms[2][7]=ms[2][7]+a3*a8;
    ms[2][8]=ms[2][8]+a3*a9; 

    ms[3][0]=ms[3][0]+a4*a1;
    ms[3][1]=ms[3][1]+a4*a2;
    ms[3][2]=ms[3][2]+a4*a3;
    ms[3][3]=ms[3][3]+a4*a4;
    ms[3][4]=ms[3][4]+a4*a5;
    ms[3][5]=ms[3][5]+a4*a6;
    ms[3][6]=ms[3][6]+a4*a7;
    ms[3][7]=ms[3][7]+a4*a8;
    ms[3][8]=ms[3][8]+a4*a9;

    ms[4][0]=ms[4][0]+a5*a1;
    ms[4][1]=ms[4][1]+a5*a2;
    ms[4][2]=ms[4][2]+a5*a3;
    ms[4][3]=ms[4][3]+a5*a4;
    ms[4][4]=ms[4][4]+a5*a5;
    ms[4][5]=ms[4][5]+a5*a6;
    ms[4][6]=ms[4][6]+a5*a7;
    ms[4][7]=ms[4][7]+a5*a8;
    ms[4][8]=ms[4][8]+a5*a9;

    ms[5][0]=ms[5][0]+a6*a1;
    ms[5][1]=ms[5][1]+a6*a2;
    ms[5][2]=ms[5][2]+a6*a3;
    ms[5][3]=ms[5][3]+a6*a4;
    ms[5][4]=ms[5][4]+a6*a5;
    ms[5][5]=ms[5][5]+a6*a6;
    ms[5][6]=ms[5][6]+a6*a7;
    ms[5][7]=ms[5][7]+a6*a8;
    ms[5][8]=ms[5][8]+a6*a9;

    ms[6][0]=ms[6][0]+a7*a1;
    ms[6][1]=ms[6][1]+a7*a2;
    ms[6][2]=ms[6][2]+a7*a3;
    ms[6][3]=ms[6][3]+a7*a4;
    ms[6][4]=ms[6][4]+a7*a5;
    ms[6][5]=ms[6][5]+a7*a6;
    ms[6][6]=ms[6][6]+a7*a7;
    ms[6][7]=ms[6][7]+a7*a8;
    ms[6][8]=ms[6][8]+a7*a9;

    ms[7][0]=ms[7][0]+a8*a1;
    ms[7][1]=ms[7][1]+a8*a2;
    ms[7][2]=ms[7][2]+a8*a3;
    ms[7][3]=ms[7][3]+a8*a4;
    ms[7][4]=ms[7][4]+a8*a5;
    ms[7][5]=ms[7][5]+a8*a6;
    ms[7][6]=ms[7][6]+a8*a7;
    ms[7][7]=ms[7][7]+a8*a8;
    ms[7][8]=ms[7][8]+a8*a9;

    ms[8][0]=ms[8][0]+a9*a1;
    ms[8][1]=ms[8][1]+a9*a2;
    ms[8][2]=ms[8][2]+a9*a3;
    ms[8][3]=ms[8][3]+a9*a4;
    ms[8][4]=ms[8][4]+a9*a5;
    ms[8][5]=ms[8][5]+a9*a6;
    ms[8][6]=ms[8][6]+a9*a7;
    ms[8][7]=ms[8][7]+a9*a8;
    ms[8][8]=ms[8][8]+a9*a9;
    
   
    sp[0]=sp[0]+a1*p;
    sp[1]=sp[1]+a2*p;
    sp[2]=sp[2]+a3*p;
    sp[3]=sp[3]+a4*p;
    sp[4]=sp[4]+a5*p;
    sp[5]=sp[5]+a6*p;
    sp[6]=sp[6]+a7*p;
    sp[7]=sp[7]+a8*p;
    sp[8]=sp[8]+a9*p;



  }
  printf("\n");
  for(i=0;i<=8;i++){
    printf("%f  %f  %f  %f\n",
	   ms[i][0],ms[i][1],ms[i][2],ms[i][3],ms[i][4],ms[i][5],ms[i][6],ms[i][7],ms[i][8],sp[i]);
  }
  printf("-------------------\n");
  for(k=0;k<=8;k++){             /* unit line */
    uu=ms[k][k];
    for(j=0;j<=8;j++){             /* make unit */
      ms[k][j]=ms[k][j]/uu;
    }
    sp[k]=sp[k]/uu;
    /*
      printf("%f  ",uu);
    */
    for(i=0;i<=8;i++){           /* other lines */
      if(i!=k){
	uu=ms[i][k];
	for(j=0;j<=8;j++){         /* subtractions */
	  ms[i][j]=ms[i][j]-uu*ms[k][j]; 
	}
	sp[i]=sp[i]-uu*sp[k];
	/*
	  printf("%f  ",uu);
	*/
      }
    }
  }
  /*
    printf("\n-------------------\n");
    for(i=0;i<=3;i++){
    printf("%f  %f  %f  %f  %f\n",ms[i][0],ms[i][1],ms[i][2],ms[i][3],sp[i]);
    }
    printf("-------------------\n"); 
  */
  ca1=sp[0];
  ca2=sp[1];
  ca3=sp[2];
  ca4=sp[3];
  ca5=sp[4];
  ca6=sp[5];
  ca7=sp[6];
  ca8=sp[7];
  ca9=sp[8];
  printf("Thscat = A1 + A2*x + A3*x*x + A4*y + A5*x*y +A6*x*x*y + A7*y*y +A8*y*y*x + A9*y*y*x*x\n");
  printf("A1=%f  A2=%f  A3=%f A4=%f A5=%f A6=%f A7=%f A8=%f A9=%f\n",ca1,ca2,ca3,ca4,ca5,ca6,ca7,ca8,ca9);
  printf("\n");
}
