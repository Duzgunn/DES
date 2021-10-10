#include <iostream>
#include <cstring>
#include <cstdlib>
#include <math.h>

using namespace std;

void DES(char key[], char message[])
{
    char message2[64];
    for (int i = 0; i < 64; i++)
    {
        message2[i] = message[i];
    }

    char left[28], right[28];

    for (int i = 0; i < 28; i++)
        left[i] = key[i];

    int x = 0;
    for (int i = 28; i < 56; i++)
    {
        right[x] = key[i];
        x++;
    }

    char keep[4], key56[57], key48[48];
    for (int i = 1; i <= 16; i++) // HER DONGUDE FARKLI ANAHTAR VE MESAJ OLUSTURMA ISLEMI
    {
        if ((i == 1) || (i == 2) || (i == 9) || (i == 16)) // BITLERI SOLA KAYDIRMA ISLEMI
        {
            keep[0] = left[0];
            keep[1] = right[0];

            for (int a = 0; a < 27; a++)
            {
                left[a] = left[a + 1];
                right[a] = right[a + 1];
            }

            left[27] = keep[0];
            right[27] = keep[1];
        }
        else // BITLERI SAGA KAYDIRMA ISLEMI
        {
            keep[0] = left[0];
            keep[1] = left[1];
            keep[2] = right[0];
            keep[3] = right[1];

            for (int a = 0; a < 26; a++)
            {
                left[a] = left[a + 2];
                right[a] = right[a + 2];
            }

            left[26] = keep[0];
            left[27] = keep[1];
            right[26] = keep[2];
            right[27] = keep[3];
        }

        for (int j = 0;  j < 28; j++) // AYRILAN BITLER BIRLESTIRILDI
        {
            key56[j] = left[j];
            key56[j + 28] = right[j];
        }

        const char daralt[] = {13, 16, 10, 23, 0, 4,
                               2, 27, 14, 5, 20, 9,
                               22, 18, 11, 3, 25, 7,
                               15, 6, 26, 19, 12, 1,
                               40, 51, 30, 36, 46, 54,
                               29, 39, 50, 44, 32, 47,
                               43, 48, 38, 55, 33, 52,
                               45, 41, 49, 35, 28, 31};

        int p;
        //cout << "key48: ";
        for (int j = 0; j < 48; j++) // DARALTMA TABLOSUNA GORE DARALTMA YAPILADI
        {
            p = daralt[j];
            key48[j] = key56[p];
            //cout << key48[i];
        }
        //cout << endl;
        //-----------------------------------------------------------------------------------------


        char message_left[32], message_right[32];

        for (int j = 0; j < 32; j++)
        {
            message_left[j] = message2[j];
            message_right[j] = message2[j+32];
        }

        /*cout << "left: ";
        for (int i = 0; i < 32; i++)
        {
            cout<< message_left[i];
        }
        cout << endl <<"right: ";                    DOGRU

        for (int i = 0; i < 32; i++)
        {
            cout<< message_right[i];
        }
        cout << endl;  */

        
        char message48[48];
        const char right_expansion[]= { 31, 0, 1, 2, 3, 4, 
                                        3, 4, 5, 6, 7, 8, 
                                        7 , 8, 9, 10, 11, 12,
                                        11, 12, 13, 14, 15, 16,
                                        15, 16, 17, 18, 19, 20, 
                                        19, 20, 21, 22, 23, 24, 
                                        23, 24, 25, 26, 27, 28,
                                        27, 28, 29, 30, 31, 0};

        int pp;
        for (int j = 0; j < 48; j++) // GENISLETME TABLOSUNA GORE GENISLETME YAPILDI
        {
            pp = right_expansion[j];
            message48[j] = message_right[pp];
        }
        

        /*cout << "message48: ";
        for (int i=0; i<48; i++)                     
            cout << message48[i];
        cout << endl;*/


        int XOR[48];
        //cout << "xor: ";
        for (int j = 0; j < 48; j++)  // XOR işlemi yapıldı
        {
            XOR[j] = message48[j] ^ key48[j];            // XOR DOGRU
           // cout << XOR[i];
        }
        //cout << endl;
        



        //************************* /S-BOXES\ *************************
        int S1[6], S2[6], S3[6], S4[6], S5[6], S6[6], S7[6], S8[6];

        //cout << "S box1: ";
        for (int j = 0; j < 6; j++)  
        {
            S1[j] = XOR[j];
            S2[j] = XOR[j+6];
            S3[j] = XOR[j+12];
            S4[j] = XOR[j+18];
            S5[j] = XOR[j+24];                // XOR AYIRMA DOGRU
            S6[j] = XOR[j+30];
            S7[j] = XOR[j+36];
            S8[j] = XOR[j+42];
            //cout << S1[i];
        }
        //cout << endl;

        //************************* /S-TABLES\ *************************
        const char S1_Table[4][16] = {14,  4,  13,	1,	2,	15,	11,	8,	3,	10,	6,	12,	5,	9,	0,	7,
	                                  0,  15,  7,	4,	14,	2,	13,	1,	10,	6,	12,	11,	9,	5,	3,	8,
	                                  4,  1,  14,	8,	13,	6,	2,	11,	15,	12,	9,	7,	3,	10,	5,	0,
	                                  15, 12,  8,   2,	4,	9,	1,	7,	5,	11,	3,	14,	10,	0,	6,	13};

        const char S2_Table[4][16] = {15,  1,  8, 14,  6, 11,  3,  4,  9,  7,  2, 13, 12,  0,  5, 10,
                                       3, 13,  4,  7, 15,  2,  8, 14, 12,  0,  1, 10,  6,  9, 11,  5,
                                       0, 14,  7, 11, 10,  4, 13,  1,  5,  8,  12, 6,  9,  3,  2, 15,
                                      13,  8, 10,  1,  3, 15,  4,  2, 11,  6,  7, 12,  0,  5, 14,  9};

        const char S3_Table[4][16] = {10,  0,  9, 14,  6,  3, 15,  5,  1, 13, 12,  7, 11,  4,  2,  8,
                                      13,  7,  0,  9,  3,  4,  6, 10,  2,  8,  5, 14, 12, 11, 15,  1,
                                      13,  6,  4,  9,  8, 15,  3,  0, 11,  1,  2, 12,  5, 10, 14,  7,
                                       1, 10, 13,  0,  6,  9,  8,  7,  4, 15, 14,  3, 11,  5,  2, 12};

        const char S4_Table[4][16] = { 7, 13, 14,  3,  0,  6,  9, 10,  1,  2,  8,  5, 11, 12,  4, 15,
                                      13,  8, 11,  5,  6, 15,  0,  3,  4,  7,  2, 12,  1, 10, 14,  9,
                                      10,  6,  9,  0, 12, 11,  7, 13, 15,  1,  3, 14,  5,  2,  8,  4,
                                       3, 15,  0,  6, 10,  1, 13,  8,  9,  4,  5, 11, 12,  7,  2, 14};
         
        const char S5_Table[4][16] = { 2, 12,  4,  1,  7, 10, 11,  6,  8,  5,  3, 15, 13,  0, 14,  9,
                                      14, 11,  2, 12,  4,  7, 13,  1,  5,  0, 15, 10,  3,  9,  8,  6,
                                       4,  2,  1, 11, 10, 13,  7,  8, 15,  9, 12,  5,  6,  3,  0, 14,
                                      11,  8, 12,  7,  1, 14,  2, 13,  6, 15,  0,  9, 10,  4,  5,  3};

        const char S6_Table[4][16] = {12,  1, 10, 15,  9,  2,  6,  8,  0, 13,  3,  4, 14,  7,  5, 11,
                                      10, 15,  4,  2,  7, 12,  9,  5,  6,  1, 13, 14,  0, 11,  3,  8,
                                       9, 14, 15,  5,  2,  8, 12,  3,  7,  0,  4, 10,  1, 13, 11,  6,
                                       4,  3,  2, 12,  9,  5, 15, 10, 11, 14,  1,  7,  6,  0,  8, 13};
                    
        const char S7_Table[4][16] = { 4, 11,  2, 14, 15,  0,  8, 13,  3, 12, 9,  7,  5, 10,  6,  1,
                                      13,  0, 11,  7,  4,  9,  1, 10, 14,  3, 5, 12,  2, 15,  8,  6,
                                       1,  4, 11, 13, 12,  3,  7, 14, 10, 15, 6,  8,  0,  5,  9,  2,
                                       6, 11, 13,  8,  1,  4,  10, 7,  9,  5, 0, 15, 14,  2,  3, 12};

        const char S8_Table[4][16] = {13,  2,  8,  4,  6, 15, 11,  1, 10,  9,  3, 14,  5,  0, 12,  7,
                                       1, 15, 13,  8, 10,  3,  7,  4, 12,  5,  6, 11,  0, 14,  9,  2,
                                       7, 11,  4,  1,  9, 12, 14,  2,  0,  6, 10, 13, 15,  3,  5,  8,
                                       2,  1, 14,  7,  4, 10,  8, 13, 15, 12,  9,  0,  3,  5,  6, 11};
        //------------------------------------------------------------------------------------------------------------
        
        
        char empty1[2], empty1_1[4], 
            empty2[2], empty2_1[4], 
            empty3[2], empty3_1[4], 
            empty4[2], empty4_1[4], 
            empty5[2], empty5_1[4], 
            empty6[2], empty6_1[4], 
            empty7[2], empty7_1[4], 
            empty8[2], empty8_1[4]; 

         for(int j = 0; j < 2; j++)  //satir icin s-box in 0 ve 5 numarali bitleri
         {
            empty1[j] = S1[j*5];
            empty2[j] = S2[j*5];
            empty3[j] = S3[j*5];
            empty4[j] = S4[j*5];
            empty5[j] = S5[j*5];
            empty6[j] = S6[j*5];
            empty7[j] = S7[j*5];
            empty8[j] = S8[j*5];
         }
        

        for (int j = 0; j < 4; j++)  //sutun icin s-box in 1,2,3,4 numarali bitleri
        {
            empty1_1[j] = S1[j+1];
            empty2_1[j] = S2[j+1];
            empty3_1[j] = S3[j+1];
            empty4_1[j] = S4[j+1];
            empty5_1[j] = S5[j+1];
            empty6_1[j] = S6[j+1];
            empty7_1[j] = S7[j+1];
            empty8_1[j] = S8[j+1];
        }
        // S-BOX LARIN BİTLERİ AYRILDI
        //------------------------------------------------------------------------------------------------
        
        
        int decimal_column1= 0, decimal_column2= 0, decimal_column3= 0, decimal_column4= 0, decimal_column5= 0, decimal_column6= 0, decimal_column7= 0, decimal_column8= 0;
        //cout << "decimal column 1: ";
        int s=0;
        for (int j = 3; j >=0; j--) //sutun icin s-box in 1,2,3,4 numarali bitleri onluk tabana cevrildi
        {
            decimal_column1 = decimal_column1 + (pow(2,s) * empty1_1[j]);
            decimal_column2 = decimal_column2 + (pow(2,s) * empty2_1[j]);
            decimal_column3 = decimal_column3 + (pow(2,s) * empty3_1[j]);
            decimal_column4 = decimal_column4 + (pow(2,s) * empty4_1[j]);
            decimal_column5 = decimal_column5 + (pow(2,s) * empty5_1[j]);
            decimal_column6 = decimal_column6 + (pow(2,s) * empty6_1[j]);
            decimal_column7 = decimal_column7 + (pow(2,s) * empty7_1[j]);
            decimal_column8 = decimal_column8 + (pow(2,s) * empty8_1[j]);
            s++;
        }
        //cout << decimal_column1 <<endl;                   
        //----------------------------------------------------------------------------------------------------------
        
        
        int decimal_row1= 0, decimal_row2= 0, decimal_row3= 0, decimal_row4= 0, decimal_row5= 0, decimal_row6= 0, decimal_row7= 0, decimal_row8= 0;
        s=0;
        //cout << "decimal row 1: ";
        for (int j = 1; j >= 0; j--) //satir icin s-box in 0 ve 5 numarali bitleri onluk tabana cevrildi
        {
            decimal_row1 = decimal_row1 + (pow(2,s) * empty1[j]);
            decimal_row2 = decimal_row2 + (pow(2,s) * empty2[j]);
            decimal_row3 = decimal_row3 + (pow(2,s) * empty3[j]);
            decimal_row4 = decimal_row4 + (pow(2,s) * empty4[j]);
            decimal_row5 = decimal_row5 + (pow(2,s) * empty5[j]);
            decimal_row6 = decimal_row6 + (pow(2,s) * empty6[j]);
            decimal_row7 = decimal_row7 + (pow(2,s) * empty7[j]);
            decimal_row8 = decimal_row8 + (pow(2,s) * empty8[j]);
            s++; 
        }
        //cout << decimal_row1 << endl;
        //------------------------------------------------------------------------------------------------

        
        int decimal_result1, decimal_result2, decimal_result3, decimal_result4, decimal_result5, decimal_result6, decimal_result7, decimal_result8;
        decimal_result1 = S1_Table[decimal_row1][decimal_column1];  
        decimal_result2 = S2_Table[decimal_row2][decimal_column2];
        decimal_result3 = S3_Table[decimal_row3][decimal_column3];
        decimal_result4 = S4_Table[decimal_row4][decimal_column4];
        decimal_result5 = S5_Table[decimal_row5][decimal_column5];   // Bulunan degerlerin s tablolarınadaki karsiligina bakılarak denk gelen deger belirlendi.
        decimal_result6 = S6_Table[decimal_row6][decimal_column6];
        decimal_result7 = S7_Table[decimal_row7][decimal_column7];
        decimal_result8 = S8_Table[decimal_row8][decimal_column8];
        //cout << "decimal result 1: " << decimal_result1 << endl;
        //----------------------------------------------------------------------------------------------------------------------------------------------------


        int binary_result1[4], binary_result2[4], binary_result3[4], binary_result4[4], binary_result5[4], binary_result6[4], binary_result7[4], binary_result8[4];
        for (int j = 3; j >= 0; j--)
        {
            if (decimal_result1 % 2 == 0)
                binary_result1[j]= 0;              
            else
                binary_result1[j]= 1;      // S Tablosundan bulunan degerler ikilik sisteme donusturuldu
            
            decimal_result1 /= 2;
        }

         for (int j = 3; j >= 0; j--)
        {
            if (decimal_result2 % 2 == 0)
                binary_result2[j]= 0;              
            else
                binary_result2[j]= 1;      // S Tablosundan bulunan degerler ikilik sisteme donusturuldu
            
            decimal_result2 /= 2;
        }

         for (int j = 3; j >= 0; j--)
        {
            if (decimal_result3 % 2 == 0)
                binary_result3[j]= 0;              
            else
                binary_result3[j]= 1;      // S Tablosundan bulunan degerler ikilik sisteme donusturuldu
            
            decimal_result3 /= 2;
        }

         for (int j = 3; j >= 0; j--)
        {
            if (decimal_result4 % 2 == 0)
                binary_result4[j]= 0;              
            else
                binary_result4[j]= 1;      // S Tablosundan bulunan degerler ikilik sisteme donusturuldu
            
            decimal_result4 /= 2;
        }

         for (int j = 3; j >= 0; j--)
        {
            if (decimal_result5 % 2 == 0)
                binary_result5[j]= 0;              
            else
                binary_result5[j]= 1;      // S Tablosundan bulunan degerler ikilik sisteme donusturuldu
            
            decimal_result5 /= 2;
        }

         for (int j = 3; j >= 0; j--)
        {
            if (decimal_result6 % 2 == 0)
                binary_result6[j]= 0;              
            else
                binary_result6[j]= 1;      // S Tablosundan bulunan degerler ikilik sisteme donusturuldu
            
            decimal_result6 /= 2;
        }

         for (int j = 3; j >= 0; j--)
        {
            if (decimal_result7 % 2 == 0)
                binary_result7[j]= 0;              
            else
                binary_result7[j]= 1;      // S Tablosundan bulunan degerler ikilik sisteme donusturuldu
            
            decimal_result7 /= 2;
        }

         for (int j = 3; j >= 0; j--)
        {
            if (decimal_result8 % 2 == 0)
                binary_result8[j]= 0;              
            else
                binary_result8[j]= 1;      // S Tablosundan bulunan degerler ikilik sisteme donusturuldu
            
            decimal_result8 /= 2;
        }

        /*cout << "tablo karsiligi: ";
         for (int i = 0; i < 4; i++)
         {
             cout << binary_result1[i];   // DOGRU CALISIYOR
         }
         cout << endl;*/
        //------------------------------------------------------------------------------------------------------------------------------------------------------

        int message32[32];
        for(int j = 0; j < 4; j++)
        {
            message32[j] = binary_result1[j];
            message32[j+4] = binary_result2[j];
            message32[j+8] = binary_result3[j];
            message32[j+12] = binary_result4[j];   // S kutulari birlestirildi
            message32[j+16] = binary_result5[j];
            message32[j+20] = binary_result6[j];
            message32[j+24] = binary_result7[j];
            message32[j+28] = binary_result8[j];
        }

        /*for(int i=0; i < 32; i++)
        {
           cout << message32[i];
        }*/
        //------------------------------------------------------------------------------------------------------------------------------------------

        int message_left2[32];
        for (int j = 0; j < 32; j++)
        {
            if (message_left[j] == '0')  // Char deger int degere donusturuldu
                message_left2[j] = 0;

            else
                message_left2[j] = 1;
        }
        
        int new_right[32];  
        for (int j = 0; j < 32; j++)
        {
            new_right[j] = message32[j] ^ message_left2[j];  // xor islemiyle Mesajin yeni sag kismi olusturuldu
        }

        /*for (int j = 0; j < 32; j++)
        {
            cout << new_right[j];             // DOGRU CALISIYOR
        }
        cout << endl;*/

        int new_left[32];
        for (int j = 0; j < 32; j++)
        {
            if (message_right[j] == '0')
                new_left[j] = 0;             // Char deger int degere donusturuldu

            else
                new_left[j] = 1;
        }
        //------------------------------------------------------------------------------------------------------------------------------------------

        int new_message[64];
        for(int j = 0; j < 32; j++)
        {
            new_message[j] = new_left[j];       // left             64 bit boyutunda yeni mesaj olusturuldu
            new_message[j+32] = new_right[j];   // right
        }

        /*for (int j = 0; j < 64; j++)
        {
            cout << new_message[j];  
        }
        cout << endl;*/
        //------------------------------------------------------------------------------------------------------------------------------------------


        char hex[13];
        for (int j = 0; j < 48; j = j + 4) // ANAHTARIN IKILIK DEGERLERI ONALTILIK DEGERLERE DONUSTURULDU
        {
            if (key48[j] == '0' && key48[j + 1] == '0' && key48[j + 2] == '0' && key48[j + 3] == '0')
                hex[j / 4] = '0';
            else if (key48[j] == '0' && key48[j + 1] == '0' && key48[j + 2] == '0' && key48[j + 3] == '1')
                hex[j / 4] = '1';
            else if (key48[j] == '0' && key48[j + 1] == '0' && key48[j + 2] == '1' && key48[j + 3] == '0')
                hex[j / 4] = '2';
            else if (key48[j] == '0' && key48[j + 1] == '0' && key48[j + 2] == '1' && key48[j + 3] == '1')
                hex[j / 4] = '3';
            else if (key48[j] == '0' && key48[j + 1] == '1' && key48[j + 2] == '0' && key48[j + 3] == '0')
                hex[j / 4] = '4';
            else if (key48[j] == '0' && key48[j + 1] == '1' && key48[j + 2] == '0' && key48[j + 3] == '1')
                hex[j / 4] = '5';
            else if (key48[j] == '0' && key48[j + 1] == '1' && key48[j + 2] == '1' && key48[j + 3] == '0')
                hex[j / 4] = '6';
            else if (key48[j] == '0' && key48[j + 1] == '1' && key48[j + 2] == '1' && key48[j + 3] == '1')
                hex[j / 4] = '7';
            else if (key48[j] == '1' && key48[j + 1] == '0' && key48[j + 2] == '0' && key48[j + 3] == '0')
                hex[j / 4] = '8';
            else if (key48[j] == '1' && key48[j + 1] == '0' && key48[j + 2] == '0' && key48[j + 3] == '1')
                hex[j / 4] = '9';
            else if (key48[j] == '1' && key48[j + 1] == '0' && key48[j + 2] == '1' && key48[j + 3] == '0')
                hex[j / 4] = 'A';
            else if (key48[j] == '1' && key48[j + 1] == '0' && key48[j + 2] == '1' && key48[j + 3] == '1')
                hex[j / 4] = 'B';
            else if (key48[j] == '1' && key48[j + 1] == '1' && key48[j + 2] == '0' && key48[j + 3] == '0')
                hex[j / 4] = 'C';
            else if (key48[j] == '1' && key48[j + 1] == '1' && key48[j + 2] == '0' && key48[j + 3] == '1')
                hex[j / 4] = 'D';
            else if (key48[j] == '1' && key48[j + 1] == '1' && key48[j + 2] == '1' && key48[j + 3] == '0')
                hex[j / 4] = 'E';
            else
                hex[j / 4] = 'F';
        }
        cout << i << ". key: " << hex << endl;



        char hex2[17];
        for (int j = 0; j < 64; j = j + 4) // MESAJIN IKILIK DEGERLER ONALTILIK DEGERLERE DONUSTURULDU
        {
            if (new_message[j] == 0 && new_message[j + 1] == 0 && new_message[j + 2] == 0 && new_message[j + 3] == 0)
                hex2[j / 4] = '0';
            else if (new_message[j] == 0 && new_message[j + 1] == 0 && new_message[j + 2] == 0 && new_message[j + 3] == 1)
                hex2[j / 4] = '1';
            else if (new_message[j] == 0 && new_message[j + 1] == 0 && new_message[j + 2] == 1 && new_message[j + 3] == 0)
                hex2[j / 4] = '2';
            else if (new_message[j] == 0 && new_message[j + 1] == 0 && new_message[j + 2] == 1 && new_message[j + 3] == 1)
                hex2[j / 4] = '3';
            else if (new_message[j] == 0 && new_message[j + 1] == 1 && new_message[j + 2] == 0 && new_message[j + 3] == 0)
                hex2[j / 4] = '4';
            else if (new_message[j] == 0 && new_message[j + 1] == 1 && new_message[j + 2] == 0 && new_message[j + 3] == 1)
                hex2[j / 4] = '5';
            else if (new_message[j] == 0 && new_message[j + 1] == 1 && new_message[j + 2] == 1 && new_message[j + 3] == 0)
                hex2[j / 4] = '6';
            else if (new_message[j] == 0 && new_message[j + 1] == 1 && new_message[j + 2] == 1 && new_message[j + 3] == 1)
                hex2[j / 4] = '7';
            else if (new_message[j] == 1 && new_message[j + 1] == 0 && new_message[j + 2] == 0 && new_message[j + 3] == 0)
                hex2[j / 4] = '8';
            else if (new_message[j] == 1 && new_message[j + 1] == 0 && new_message[j + 2] == 0 && new_message[j + 3] == 1)
                hex2[j / 4] = '9';
            else if (new_message[j] == 1 && new_message[j + 1] == 0 && new_message[j + 2] == 1 && new_message[j + 3] == 0)
                hex2[j / 4] = 'A';
            else if (new_message[j] == 1 && new_message[j + 1] == 0 && new_message[j + 2] == 1 && new_message[j + 3] == 1)
                hex2[j / 4] = 'B';
            else if (new_message[j] == 1 && new_message[j + 1] == 1 && new_message[j + 2] == 0 && new_message[j + 3] == 0)
                hex2[j / 4] = 'C';
            else if (new_message[j] == 1 && new_message[j + 1] == 1 && new_message[j + 2] == 0 && new_message[j + 3] == 1)
                hex2[j / 4] = 'D';
            else if (new_message[j] == 1 && new_message[j + 1] == 1 && new_message[j + 2] == 1 && new_message[j + 3] == 0)
                hex2[j / 4] = 'E';
            else
                hex2[j / 4] = 'F';
        }

        cout << i << ". message: ";
        for (int j = 0; j < 16; j++)
        {
            cout << hex2[j];                 // MESAJ YAZDIRMA ISLEMI
        }
        cout << endl;

        for (int j = 0; j < 64; j++)
        {
            if (new_message[j] == 0)
                message2[j] = '0';     // Yeni mesaj eski mesaja atandı (Bu sayede her turda mesajın kendini tekrarlaması önlenerek yeni bir mesaj olusturulmakta)
                                       // Yeni mesaj "int", eski mesaj "char" degerinde oldugu icin atama islemu bu seklilde yapildı.
            else
                message2[j] = '1';
        }
        
    }

    const char final_permutation[64] = {39, 7, 47, 15, 55, 23, 63, 31,
                                        38, 6, 46, 14, 54, 22, 62, 30,
                                        37, 5, 45, 13, 53, 21, 61, 29,
                                        36, 4, 44, 12, 52, 20, 60, 28,
                                        35, 3, 43, 11, 51, 19, 59, 27,
                                        34, 2, 42, 10, 50, 18, 58, 26,
                                        33, 1, 41,  9, 49, 17, 57, 25,
                                        32, 0, 40,  8, 48, 16, 56, 24};
    
    int abc;
    char last_message[64];
    for (int j = 0; j < 64; j++)
    {
        abc = final_permutation[j];
        last_message[j] = message2[abc];
    }
    
    char hex3[17]; // Son karistirma islemi (16'lik döngü bittigi icin yeni bir "binary to hex" yapilmali) 
        for (int j = 0; j < 64; j = j + 4) // MESAJIN SON HALININ IKILIK DEGERLERI ONALTILIK DEGERLERE DONUSTURULDU
        {
            if (last_message[j] == '0' && last_message[j + 1] == '0' && key48[j + 2] == '0' && key48[j + 3] == '0')
                hex3[j / 4] = '0';
            else if (last_message[j] == '0' && last_message[j + 1] == '0' && last_message[j + 2] == '0' && last_message[j + 3] == '1')
                hex3[j / 4] = '1';
            else if (last_message[j] == '0' && last_message[j + 1] == '0' && last_message[j + 2] == '1' && last_message[j + 3] == '0')
                hex3[j / 4] = '2';
            else if (last_message[j] == '0' && last_message[j + 1] == '0' && last_message[j + 2] == '1' && last_message[j + 3] == '1')
                hex3[j / 4] = '3';
            else if (last_message[j] == '0' && last_message[j + 1] == '1' && last_message[j + 2] == '0' && last_message[j + 3] == '0')
                hex3[j / 4] = '4';
            else if (last_message[j] == '0' && last_message[j + 1] == '1' && last_message[j + 2] == '0' && last_message[j + 3] == '1')
                hex3[j / 4] = '5';
            else if (last_message[j] == '0' && last_message[j + 1] == '1' && last_message[j + 2] == '1' && last_message[j + 3] == '0')
                hex3[j / 4] = '6';
            else if (last_message[j] == '0' && last_message[j + 1] == '1' && last_message[j + 2] == '1' && last_message[j + 3] == '1')
                hex3[j / 4] = '7';
            else if (last_message[j] == '1' && last_message[j + 1] == '0' && last_message[j + 2] == '0' && last_message[j + 3] == '0')
                hex3[j / 4] = '8';
            else if (last_message[j] == '1' && last_message[j + 1] == '0' && last_message[j + 2] == '0' && last_message[j + 3] == '1')
                hex3[j / 4] = '9';
            else if (last_message[j] == '1' && last_message[j + 1] == '0' && last_message[j + 2] == '1' && last_message[j + 3] == '0')
                hex3[j / 4] = 'A';
            else if (last_message[j] == '1' && last_message[j + 1] == '0' && last_message[j + 2] == '1' && last_message[j + 3] == '1')
                hex3[j / 4] = 'B';
            else if (last_message[j] == '1' && last_message[j + 1] == '1' && last_message[j + 2] == '0' && last_message[j + 3] == '0')
                hex3[j / 4] = 'C';
            else if (last_message[j] == '1' && last_message[j + 1] == '1' && last_message[j + 2] == '0' && last_message[j + 3] == '1')
                hex3[j / 4] = 'D';
            else if (last_message[j] == '1' && last_message[j + 1] == '1' && last_message[j + 2] == '1' && last_message[j + 3] == '0')
                hex3[j / 4] = 'E';
            else
                hex3[j / 4] = 'F';
        }

        cout << "Final message: ";
        for (int j = 0; j < 16; j++)
        {
            cout << hex3[j];                 // MESAJ YAZDIRMA ISLEMI
        }
        cout << endl;
    
}

int main()
{
    char bin[65] = "";
    char key[17];

    go:
    cout << "Lutfen 64 bitlik hexadecimal anahtar giriniz: ";
    cin >> key;

    bool a = 1;
    for (int i = 0; i< 16; i++) //GIRILEN ONALTILIK DEGERLER IKILIK DEGERLERE DONUSTURULDU
    {
        switch (key[i])
        {
        case '0':
            strcat(bin, "0000");
            break;
        case '1':
            strcat(bin, "0001");
            break;
        case '2':
            strcat(bin, "0010");
            break;
        case '3':
            strcat(bin, "0011");
            break;
        case '4':
            strcat(bin, "0100");
            break;
        case '5':
            strcat(bin, "0101");
            break;
        case '6':
            strcat(bin, "0110");
            break;
        case '7':
            strcat(bin, "0111");
            break;
        case '8':
            strcat(bin, "1000");
            break;
        case '9':
            strcat(bin, "1001");
            break;
        case 'a':
        case 'A':
            strcat(bin, "1010");
            break;
        case 'b':
        case 'B':
            strcat(bin, "1011");
            break;
        case 'c':
        case 'C':
            strcat(bin, "1100");
            break;
        case 'd':
        case 'D':
            strcat(bin, "1101");
            break;
        case 'e':
        case 'E':
            strcat(bin, "1110");
            break;
        case 'f':
        case 'F':
            strcat(bin, "1111");
            break;
        default:
            a = 0;
            break;
        }
    }
    

    char bin2[57];
    if (a) // GIRILEN DEGERIN ONALTILIK TABANDA OLUP OLMADIGI KONTROL EDILDI
    {
        const char degistir[] = {56, 48, 40, 32, 24, 16, 8,
                                 0, 57, 49, 41, 33, 25, 17,
                                 9, 1, 58, 50, 42, 34, 26,
                                 18, 10, 2, 59, 51, 43, 35,
                                 62, 54, 46, 38, 30, 22, 14,
                                 6, 61, 53, 45, 37, 29, 21,
                                 13, 5, 60, 52, 44, 36, 28,
                                 20, 12, 4, 27, 19, 11, 3};

        cout << "Girilen sayinin binary degeri: " << bin << endl;

         // PARITE BITLER ATILDI VE "degistir" TABLOSUNA UYGUN YERLESTIRME YAPILDI.
        int z;
        for (int i = 0; i < 56; i++)
        {
            z = degistir[i];
            bin2[i] = bin[z];
        }
    }

    else
    {
        cout << "Gecersiz deger girdiniz." << endl;
        goto go;
    }


    //************************************ \ MESSAGE / *********************************



    char message[17];
    char bin_message[65] = "";

    go2:

    cout << "Lutfen 64 bitlik hexadecimal mesaj giriniz: ";
    cin >> message;

    bool k = 1;
    for (int i = 0; i< 16; i++) 
    {
        switch (message[i])
        {
        case '0':
            strcat(bin_message, "0000");
            break;
        case '1':
            strcat(bin_message, "0001");
            break;
        case '2':
            strcat(bin_message, "0010");
            break;
        case '3':
            strcat(bin_message, "0011");
            break;
        case '4':
            strcat(bin_message, "0100");
            break;
        case '5':
            strcat(bin_message, "0101");
            break;
        case '6':
            strcat(bin_message, "0110");
            break;
        case '7':
            strcat(bin_message, "0111");
            break;
        case '8':
            strcat(bin_message, "1000");
            break;
        case '9':
            strcat(bin_message, "1001");
            break;
        case 'a':
        case 'A':
            strcat(bin_message, "1010");
            break;
        case 'b':
        case 'B':
            strcat(bin_message, "1011");
            break;
        case 'c':
        case 'C':
            strcat(bin_message, "1100");
            break;
        case 'd':
        case 'D':
            strcat(bin_message, "1101");
            break;
        case 'e':
        case 'E':
            strcat(bin_message, "1110");
            break;
        case 'f':
        case 'F':
            strcat(bin_message, "1111");
            break;
        default:
            k = 0;
            break;
        }
    }

     if (k) // GIRILEN DEGERIN ONALTILIK TABANDA OLUP OLMADIGI KONTROL EDILDI
    {
        cout << "Girilen sayinin binary degeri: " << bin_message << endl;

        const char degistir_message[] = {57, 49, 41, 33, 25, 17, 9,  1,
                                         59, 51, 43, 35, 27, 19, 11, 3,
                                         61, 53, 45, 37, 29, 21, 13, 5,
                                         63, 55, 47, 39, 31, 23, 15, 7,
                                         56, 50, 40, 32, 24, 16, 10, 0,
                                         58, 50, 42, 34, 26, 18, 10, 4,
                                         60, 52, 44, 36, 28, 20, 12, 4,
                                         62, 54, 46, 38, 30, 22, 14, 6};
        

        char bin_message2[57]; 
        int p;

        for (int i = 0; i < 64; i++) // PARITE BITLER ATILDI VE "degistir" TABLOSUNA UYGUN YERLESTIRME YAPILDI.
        {
            p = degistir_message[i];
            bin_message2[i] = bin_message[p];
        }

        /*cout << "mesaj tablo ilk degeri: ";
        for (int i = 0; i < 56; i++)                DOGRU
             cout << bin_message2[i]; 

        cout << endl;*/

        DES(bin2, bin_message2);
    }

    else
    {
        cout << "Gecersiz deger girdiniz." << endl;
        goto go2;
    }

    return 0;
}
