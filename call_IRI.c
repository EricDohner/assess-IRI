#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

void read_jf(int jf[50]);
void read_inputs(int* jmag, float* alati, float* along, int* iyyyy, int* mmdd, float* dhour, float* heibeg, float* heiend, float* heistep);
void write_outputs(float a[][20], float b[], float hgrid[], int hsteps);

extern void iri_sub_(int jf[],int *jmag, float *alati,float *along, int *iyyyy, int *mmdd,float *dhour, float *heibeg, float *heiend, float *heistep, float outf[1000][20], float oarr[100]);
extern void read_ig_rz_();
extern void readapf107_();
extern void iri_web_(int *jmag,int jf[],float *alati,float *along,int *iyyyy,int *mmdd,int *iut,float *dhour, float *height,float *h_tec_max,int *ivar,float *vbeg,float *vend, float* vstp, float a[][20], float b[][100]);

float oar[100];

int main(void)
{
    
    //initialize parameters
    int jf[50];
   
    int i;
    int jmag;
    float alati;
    float along;
    int iyyyy;
    int mmdd;
    float dhour;
    float heibeg;
    float heiend;
    float heistep;
    int ivar = 1;
    int iut = 1;
    float h_tec_max = 0;
    float height = 100;
    
//     float outf[1000][20];
//     float oarr[100];
    float outf[1000][20];
    float oarr[100];
    

    
    for(i = 0; i<100; i++){
     oar[i] = -1;   
    }
    
    read_jf(jf); // Read the values of the JF array: boolean array to set various IRI internal switches
    read_inputs(&jmag, &alati, &along, &iyyyy, &mmdd, &dhour, &heibeg, &heiend, &heistep); // read input values from inputs.txt
    
    jf[21] = 0; //look at ion concentration in m^-3 rather than %
    
    //create height grid for EDP
    
    const int hsteps = (int)((heiend - heibeg)/heistep) + 1;
    
   printf("hsteps = %d\n", hsteps);
    
    float hgrid[hsteps];

    for(i = 0; i<hsteps; i++){
        hgrid[i] = heibeg + i*heistep;
    }


    
//     printf("%d %f %f %d %d %f %f %f %f\n", jmag, alati, along, iyyyy, mmdd, dhour, heibeg, heiend, heistep);
    
    read_ig_rz_();
    readapf107_();
    
    iri_sub_( jf, &jmag, &alati, &along, &iyyyy, &mmdd, &dhour, &heibeg, &heiend, &heistep, outf, oarr);
    
    
//     iri_web_(&jmag,jf,&alati,&along,&iyyyy,&mmdd,&iut,&dhour,&height,&h_tec_max,&ivar,&heibeg,&heiend,&heistep,a, b);
    
    write_outputs(outf, oarr, hgrid, hsteps);
    
    
    return 0;
}
void write_outputs(float a[][20], float b[], float hgrid[], int hsteps){
     
    
    //First file contains standard outputs like HMF2, etc.
    FILE *oarroutputs = fopen("outputparams.txt", "w");
    
    fprintf(oarroutputs, "%f %f#NMF2, m^-3 HMF2, km\n", b[0], b[1]);
    fprintf(oarroutputs, "%f %f#NMF1, m^-3 HMF1, km\n", b[2], b[3]);
    fprintf(oarroutputs, "%f %f#NME, m^-3 HME, km\n", b[4], b[5]);
    fprintf(oarroutputs, "%f %f#NMD, m^-3 HMD, km\n", b[6], b[7]);
    fprintf(oarroutputs, "%f #HHALF, KM\n", b[8]);
    fprintf(oarroutputs, "%f #B0, KM\n", b[9]);
    fprintf(oarroutputs, "%f #B1\n", b[34]);
    fprintf(oarroutputs, "%f #VALLEY-BASE, km\n", b[10]);
    fprintf(oarroutputs, "%f #VALLEY-TOP, km\n", b[11]);
//     fprintf(oarroutputs, "%f #TEC, m^-2\n", b[37]); //Only valid if IRI_WEB is used instead of iri_sub
    
    int i;
    
    
    //Remaining files contain height vs. various data: Ne, plasma frequency, and ion concentrations
    FILE *hvse = fopen("hvse.txt", "w");
    
    fprintf(hvse, "# e(m^-3) h(km) \n");
    
    for(i = 0; i <hsteps; i++){
        fprintf(hvse, "%f %f\n", a[i][0], hgrid[i]);
    }
    fclose(hvse);
    
    FILE *hvsw = fopen("hvsplasmafreq.txt", "w");
    
    fprintf(hvsw, "#plasma w (MHz) h(km) \n");
    
    for(i = 0; i <hsteps; i++){
        
        if(a[i][0]>0){fprintf(hvsw, "%f %f\n", 9.0*sqrtf((a[i][0]))/1000000.0, hgrid[i]);}
    }
    fclose(hvsw);
    
    FILE *hvsOions = fopen("hvsOions.txt", "w");
    
    fprintf(hvsOions, "#h(km) O+ ions (m^-3) \n");
    
    for(i = 0; i <hsteps; i++){
        fprintf(hvsOions, "%f %f\n", a[i][4], hgrid[i]);
    }
    fclose(hvsOions);
    
    FILE *hvsHions = fopen("hvsHions.txt", "w");
    
    for(i = 0; i <hsteps; i++){
        fprintf(hvsHions, "%f %f\n", a[i][5], hgrid[i]);
    }
    fclose(hvsHions);
    
    FILE *hvsHEions = fopen("hvsHEions.txt", "w");
    
    for(i = 0; i <hsteps; i++){
        fprintf(hvsHEions, "%f %f\n", a[i][6], hgrid[i]);
    }
    fclose(hvsHEions);
    
    FILE *hvsH2ions = fopen("hvsO2ions.txt", "w");
    
    for(i = 0; i <hsteps; i++){
        fprintf(hvsH2ions, "%f %f\n", a[i][7], hgrid[i]);
    }
    fclose(hvsH2ions);
    
    FILE *hvsNOions = fopen("hvsNOions.txt", "w");
    
    for(i = 0; i <hsteps; i++){
        fprintf(hvsNOions, "%f %f\n", a[i][8], hgrid[i]);
    }
    fclose(hvsNOions);
    
    float ionsum;
    int j;
    FILE *hvsallions = fopen("hvsallions.txt", "w");
    
    for(i = 0; i <hsteps; i++){
        ionsum = 0;
        for(j = 4; j<12; j++){
            ionsum += a[i][j];
        }
        
        fprintf(hvsNOions, "%f %f\n", ionsum, hgrid[i]);
    }
    fclose(hvsNOions);
    
    
}

//read_inputs reads the input parameters from a file. Use -DDD format for day and HH.FF (11.5 = 1130) for time.
void read_inputs(int* jmag, float* alati, float* along, int* iyyyy, int* mmdd, float* dhour, float* heibeg, float* heiend, float* heistep){
    
    
    FILE* inputs = fopen("inputs.txt", "r");
    if(inputs == NULL){perror("inputs.txt does not exist");}
    
    char inputstring[200];
    
    if( fgets (inputstring, 200, inputs)!=NULL ) 
    {
      sscanf(inputstring, "%d %f %f %d %d %f %f %f %f", jmag, alati, along, iyyyy, mmdd, dhour, heibeg, heiend, heistep);
    }
    
}


//read_jf reads a list of integers (1 and 0) for the boolean switch values in the array JF from the file "indat_jf.txt".
void read_jf(int jf[50]){
    
    FILE* jf_file = fopen("indat_jf.txt", "r");
    if(jf_file == NULL){perror("indat_jf.txt does not exist");}
    
    int i = 0;
    int j;
    char buff[1];
    
    while(fscanf(jf_file, "%s", buff) == 1){
        j = atoi(buff);
        jf[i] = j;
        i++;
    }
    return;
}

