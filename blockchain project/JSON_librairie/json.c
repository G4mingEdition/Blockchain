#include "json.h"

unsigned jsonPrimitive(char *chaineJson, char *nomAttribut, char *resultat,unsigned dim,char *messageErreur)
{
    char *ptr, *ptrDebut, *ptrFin;
    char nomAttribut2[40]="\"\0";
    int longueur, i;
    for(i=0; i<dim; i++) resultat[i]=' ';
    strcat(nomAttribut2, nomAttribut);
    strcat(nomAttribut2, "\"");
    ptr = strstr(chaineJson, nomAttribut2);
    if ( ptr==NULL )   // pas trouvé
    {
        strcpy(resultat,"");
        strcpy(messageErreur, "L'attribut n'a pas ete trouve!");
        return RESULTAT_ERREUR;
    }
    // attribut trouvé, recherche de sa valeur
    ptrDebut = strchr(ptr+strlen(nomAttribut)+2,'\"');
    if (ptrDebut==NULL)
    {
        strcpy(resultat,"");
        strcpy(messageErreur, "Pas de valeur pour l'attribut!");
        return RESULTAT_ERREUR;
    }
    ptrFin = strchr(ptrDebut+1, '\"');
    if (ptrFin==NULL)
    {
        strcpy(resultat,"");
        strcpy(messageErreur, "Pas de valeur pour l'attribut!");
        return RESULTAT_ERREUR;
    }
    longueur = ((int) (ptrFin-ptrDebut))-1;
    strncpy(resultat, ptrDebut+1,longueur);
    *(resultat+longueur) = '\0';
    strcpy(messageErreur, "Pas d'erreur");
    return RESULTAT_OK;
}
unsigned jsonArray(char *chaineJson, char *nomAttribut, char resultats[][TAILLE_MAX_1650], unsigned *nbElements, char *messageErreur)
{
    int c;
    char nomAttribut2[40]="\"\0";
    char *ptr, *ptrDebut;
    int cptCr, cptAc, longueur;
    strcat(nomAttribut2, nomAttribut);
    strcat(nomAttribut2, "\"");
    ptr = strstr(chaineJson, nomAttribut2);
    *nbElements=0;
    if ( ptr==NULL )   // pas trouvé
    {
        strcpy(messageErreur, "L'attribut n'a pas ete trouve!");
        return RESULTAT_ERREUR;
    }
    ptr = strchr(ptr,'[');
    if ( ptr==NULL)
    {
        strcpy(messageErreur, "Pas de tableau pour l'attribut!");
        return RESULTAT_ERREUR;
    }

    // début du tableau trouvé
    cptCr=1;
    cptAc=0;
    ptr++;
    c = *ptr;
    while( c!='\0' )
    {
        if ( c=='}')
        {
            cptAc--;
            if ( cptAc<0 )
            {
                strcpy(messageErreur, "Trop de '}'");
                return RESULTAT_ERREUR;
            }
            if ( cptAc==0 )
            {
                // fin d'un élément
                longueur = (int)(ptr-ptrDebut+1);
                strncpy(resultats[*nbElements], ptrDebut,longueur);
                strcpy(resultats[*nbElements]+longueur+1,"\n\0");
                (*nbElements)++;
            }
        }
        else  if ( c=='{')
        {
            if (cptAc==0)
            {
                // nouvel élément
                ptrDebut = ptr;
            }
            cptAc++;

        }
        else if (c=='[')
            cptCr++;
        else if (c==']')
        {
            cptCr--;
            if ( cptCr<0 )
            {
                strcpy(messageErreur, "Trop de ']'");
                return RESULTAT_ERREUR;
            }
            if ( cptCr==0 )
            {
                // fin du tableau
                strcpy(messageErreur, "Pas d'erreur");
                return RESULTAT_OK;
            }
        }
        ptr++;
        c = *ptr;
    }
    strcpy(messageErreur, "Pas de fin de tableau!");
    return RESULTAT_ERREUR;

}
unsigned jsonArrayFile(char *nomFichierIn, char *nomAttribut, char *nomFichierOut, char *messageErreur)
{
    FILE *fpIn, *fpOut;
    int c;
    int i=0;
    unsigned trouve =0;
    char nomAttribut2[40]="\"\0";
    char enregOut[2000];
    char *ptr;
    int cptCr, cptAc;
    fpIn = fopen(nomFichierIn,"r");
    if(fpIn == NULL)
    {
        strcpy(messageErreur, "Erreur lors de l'ouverture du fichier in");
        fclose(fpIn);
        return RESULTAT_ERREUR;
    }
    strcat(nomAttribut2, nomAttribut);
    strcat(nomAttribut2, "\"");
    do
    {
        c = fgetc(fpIn);
        if( feof(fpIn) )
        {
            strcpy(messageErreur, "L'attribut n'a pas ete trouve!");
            fclose(fpIn);
            return RESULTAT_ERREUR;
        }
        if ( c==nomAttribut2[i])
        {
            i++;
            if (i==strlen(nomAttribut2)) trouve=1;
        }
        else i=0;
    }
    while(!trouve);

    // ouverture du fichier out
    fpOut = fopen(nomFichierOut,"w");
    if(fpOut == NULL)
    {
        strcpy(messageErreur, "Erreur lors de l'ouverture du fichier out");
        fclose(fpOut);
        fclose(fpIn);
        return RESULTAT_ERREUR;
    }

    cptCr=0;
    do // recherche du début du tableau
    {
        c = fgetc(fpIn);
        if( feof(fpIn) )
        {
            strcpy(messageErreur, "Pas de tableau pour l'attribut!");
            fclose(fpOut);
            fclose(fpIn);
            return RESULTAT_ERREUR;
        }
        if (c=='[')
        {
            cptCr++;
        }
    }
    while(cptCr==0);

    // début du tableau trouvé
    cptAc=0;
    ptr = enregOut;
    c = fgetc(fpIn);
    while(!feof(fpIn) )
    {
        if ( c=='}')
        {
            cptAc--;
            if ( cptAc<0 )
            {
                strcpy(messageErreur, "Trop de '}'");
                fclose(fpOut);
                fclose(fpIn);
                return RESULTAT_ERREUR;
            }
            if ( cptAc==0 )
            {
                // fin d'un élément
                *ptr=c;
                ptr++;
                strcpy(ptr,"\n\0");
                fputs(enregOut, fpOut);
                ptr=NULL;
            }
        }
        else  if ( c=='{')
        {
            if (cptAc==0)
            {
                // nouvel élément
                ptr = enregOut;
            }
            cptAc++;

        }
        else if (c=='[')
            cptCr++;
        else if (c==']')
        {
            cptCr--;
            if ( cptCr<0 )
            {
                strcpy(messageErreur, "Trop de ']'");
                fclose(fpOut);
                fclose(fpIn);
                return RESULTAT_ERREUR;
            }
            if ( cptCr==0 )
            {
                // fin du tableau
                strcpy(messageErreur, "Pas d'erreur");
                fclose(fpOut);
                fclose(fpIn);
                return RESULTAT_OK;
            }
        }
        if ( ptr!=NULL)
        {
            *ptr = c;
            ptr++;
        }
        c = fgetc(fpIn);
    }
    strcpy(messageErreur, "Pas de fin de tableau!");
    fclose(fpIn);
    fclose(fpOut);
    return RESULTAT_ERREUR;
}
