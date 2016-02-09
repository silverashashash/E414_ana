#include <stdio.h>
#include <math.h>
//6 parameters 

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
  float a,b,c,d,e,f;
  float uu;
  float ca,cb,cc,cd,ce,cf;
  static float ms[6][6]={
    {0.0,0.0,0.0,0.0,0.0,0.0},
    {0.0,0.0,0.0,0.0,0.0,0.0},
    {0.0,0.0,0.0,0.0,0.0,0.0},
    {0.0,0.0,0.0,0.0,0.0,0.0},
    {0.0,0.0,0.0,0.0,0.0,0.0},
    {0.0,0.0,0.0,0.0,0.0,0.0},
    };
  static float sp[6]={0.0,0.0,0.0,0.0,0.0,0.0};
FILE *fp;
  fp = fopen("6para.dat","r");
  while((ff=fscanf(fp,"%f %f %f",&p,&t,&x)) != EOF){
    a=1;
    b=x;
    c=x*x;
    d=t;
    e=x*t;
    f=x*x*t;
    ms[0][0]=ms[0][0]+a*a;
    ms[0][1]=ms[0][1]+a*b;
    ms[0][2]=ms[0][2]+a*c;
    ms[0][3]=ms[0][3]+a*d;
    ms[0][4]=ms[0][4]+a*e;
    ms[0][5]=ms[0][5]+a*f;
    ms[1][0]=ms[1][0]+b*a;
    ms[1][1]=ms[1][1]+b*b;
    ms[1][2]=ms[1][2]+b*c;
    ms[1][3]=ms[1][3]+b*d;
    ms[1][4]=ms[1][4]+b*e;
    ms[1][5]=ms[1][5]+b*f;
    ms[2][0]=ms[2][0]+c*a;
    ms[2][1]=ms[2][1]+c*b;
    ms[2][2]=ms[2][2]+c*c;
    ms[2][3]=ms[2][3]+c*d;
    ms[2][4]=ms[2][4]+c*e;
    ms[2][5]=ms[2][5]+c*f;
    ms[3][0]=ms[3][0]+d*a;
    ms[3][1]=ms[3][1]+d*b;
    ms[3][2]=ms[3][2]+d*c;
    ms[3][3]=ms[3][3]+d*d;
    ms[3][4]=ms[3][4]+d*e;
    ms[3][5]=ms[3][5]+d*f;
    ms[4][0]=ms[4][0]+e*a;
    ms[4][1]=ms[4][1]+e*b;
    ms[4][2]=ms[4][2]+e*c;
    ms[4][3]=ms[4][3]+e*d;
    ms[4][4]=ms[4][4]+e*e;
    ms[4][5]=ms[4][5]+e*f;
    ms[5][0]=ms[5][0]+f*a;
    ms[5][1]=ms[5][1]+f*b;
    ms[5][2]=ms[5][2]+f*c;
    ms[5][3]=ms[5][3]+f*d;
    ms[5][4]=ms[5][4]+f*e;
    ms[5][5]=ms[5][5]+f*f;
    sp[0]=sp[0]+a*p;
    sp[1]=sp[1]+b*p;
    sp[2]=sp[2]+c*p;
    sp[3]=sp[3]+d*p;
    sp[4]=sp[4]+e*p;
    sp[5]=sp[5]+f*p;
  }
  printf("\n");
  for(i=0;i<=5;i++){
    printf("%f  %f  %f  %f\n",
	   ms[i][0],ms[i][1],ms[i][2],ms[i][3],ms[i][4],ms[i][5],sp[i]);
  }
  printf("-------------------\n");
  for(k=0;k<=5;k++){             /* unit line */
    uu=ms[k][k];
    for(j=0;j<=5;j++){             /* make unit */
      ms[k][j]=ms[k][j]/uu;
    }
    sp[k]=sp[k]/uu;
    /*
      printf("%f  ",uu);
    */
    for(i=0;i<=5;i++){           /* other lines */
      if(i!=k){
	uu=ms[i][k];
	for(j=0;j<=5;j++){         /* subtractions */
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
  ca=sp[0];
  cb=sp[1];
  cc=sp[2];
  cd=sp[3];
  ce=sp[4];
  cf=sp[5];
  printf("Thscat = A + B*x + C*x*x + D*t + E*t*x + F*t*x*x*\n");
  printf("A=%f  B=%f  C=%f D=%f E=%f F=%f\n",ca,cb,cc,cd,ce,cf);
  printf("\n");
}
