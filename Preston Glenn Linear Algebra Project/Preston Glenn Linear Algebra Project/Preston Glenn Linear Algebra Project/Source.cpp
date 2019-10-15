#include <ios>
#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <math.h>

using namespace std;


int  **multiply(int KeysizeM, int middleSize, int sizeN, int** key, int ** message);
int **convertString(string message, int sizeOfSquareKey, int & messageLength);
int convertLetterstoInt(char letter);
char convertIntToChar(int letter);
int **keyCreator(int  size);
bool checkForInvertibility(int**array, int size);

double ** invertMatrices(double**array, int sizeM, int sizeN);
int determinateCalc(int**array, int size);
void printArray(int **& array, int m, int n);
string convertMatrixtoString(int ** matrix, int size, int length);
bool isInt(double num);
int ** createDecrypterKey2D(int** oldKey);
bool continueProgram = true;

int main()
{

   const int size = 2;
   double determinate;



   int messageLength;
   int ** arrays;
   int ** encryptedMatrix;


   int ** decrypterKey = nullptr;
   int ** decryptedMatrix;

   int choice;
   int **key = nullptr;

   //Step 1. Get Key
   bool badDeterminate = true;
   /*
      while (badDeterminate)
      {
         key = keyCreator(size);
         while (!checkForInvertibility(key, size))
         {

            cout << "That key is not valid, please enter one that is invertible." << endl;
            key = keyCreator(size);
         }
         determinate = determinateCalc(key, size);
         if (isInt(determinate))
            badDeterminate = false;
         else
            cout << "Please use a key with a determinate that is an int value" << endl;
      }

      */

   do {


      cout << "Would you like to encrypt a message or a decrypt a message? Type \n 1. Encrypt. \n 2. Decrypt \n 3. Exit\n\n";
      cin >> choice;

      switch (choice)
      {
      case 1:
      {
         int **key = nullptr;


         bool badDeterminate = true;
         cout << "Please enter the 2X2 key Wwhos determinate is not divisible by 3." << endl << endl;
         while (badDeterminate)
         {
            key = keyCreator(size);
            while (!checkForInvertibility(key, size) || (determinateCalc(key, 2) % 3 == 0))
            {

               cout << "That key is not valid, please enter one that is invertible with a determinate not divisible by 3." << endl;
               key = keyCreator(size);
            }
            determinate = determinateCalc(key, size);
            if (isInt(determinate))
               badDeterminate = false;
            else
               cout << "Please use a key with a determinate that is an int value" << endl;
         }





         string messageString;
         int **message = new int*[size];

         cout << "What is the message you would like to encrypt? ALL CAPS" << endl << endl;
         cin.ignore();
         getline(cin, messageString);

         message = convertString(messageString, size, messageLength);

         cout << endl << endl << endl;
         printArray(message, 2, messageLength);
         cout << endl << endl << endl;

         //Step 5. Multiply message matrix by key
         encryptedMatrix = multiply(size, size, messageLength, key, message);

         cout << endl << endl << endl;
         printArray(encryptedMatrix, 2, messageLength);
         cout << endl << endl << endl;


         string encryptedMessage = convertMatrixtoString(encryptedMatrix, size, messageLength);
         cout << "Your encrypted message is: \n\n\n" << encryptedMessage << endl;


         break;
      }
      case 2:
      {
         cout << "Please enter the 2X2 key." << endl << endl;

         int **message = new int*[size];
         bool badDeterminate = true;
         int **key = nullptr;

         while (badDeterminate)
         {
            key = keyCreator(size);
            while (!checkForInvertibility(key, size) || (determinateCalc(key, 2) % 3 == 0))
            {

               cout << "That key is not valid, please enter one that is invertible with a determinate that is not divisible by 3." << endl;
               key = keyCreator(size);
            }
            determinate = determinateCalc(key, size);
            if (isInt(determinate))
               badDeterminate = false;
            else
               cout << "Please use a key with a determinate that is an int value" << endl;
         }


         decrypterKey = createDecrypterKey2D(key);


         cout << endl << endl << endl;
         printArray(decrypterKey, 2, 2);
         cout << endl << endl << endl;

         string messageString;

         cout << "What is the message you would like to decrypt? " << endl << endl;
         cin.ignore();
         getline(cin, messageString);

         message = convertString(messageString, size, messageLength);

         cout << endl << endl << endl;
         printArray(message, 2, messageLength);
         cout << endl << endl << endl;



         decryptedMatrix = multiply(2, 2, messageLength, decrypterKey, message);

         cout << endl << endl << endl;
         printArray(decryptedMatrix, 2, messageLength);
         cout << endl << endl << endl;


         string decryptedMessage = convertMatrixtoString(decryptedMatrix, size, messageLength);
         cout << "The decrypted message is:\n" << decryptedMessage << endl << endl;
         break;
      }
      default:
         continueProgram = false;
         break;
      }






   } while (continueProgram);


   system("pause");
   return 0;


}





//based on assumption that the key is square
int  **multiply(int KeysizeM, int middleSize, int sizeN, int** key, int ** message)
{
   int **newArray = new int*[KeysizeM];

   for (int i = 0; i < KeysizeM; ++i) {
      newArray[i] = new int[sizeN];
   }


   for (int j = 0; j < sizeN; j++)
   {
      for (int m = 0; m < KeysizeM; m++)
      {
         int count = 0;
         for (int n = 0; n < middleSize; n++)
         {
            count += key[m][n] * message[n][j];
         }
         newArray[m][j] = count % 27;

      }
   }
   return newArray;
}







int **convertString(string message, int sizeOfSquareKey, int & messageLength)
{
   int length = size(message);
   int newLength = length;

   //make length equal to m*n
   while ((newLength % sizeOfSquareKey) != 0)
   {
      newLength++;
      message += " ";
   }
   int sizeMnew = sizeOfSquareKey;
   int sizeNnew = newLength / sizeOfSquareKey;
   messageLength = sizeNnew;

   //creates new 2d array of pointers
   int **messageArray = new int*[sizeMnew];
   for (int i = 0; i < sizeMnew; ++i) {
      messageArray[i] = new int[sizeNnew];
   }

   int count = 0;

   for (int i = 0; i < sizeNnew; i++)
   {
      for (int j = 0; j < sizeOfSquareKey; j++, count++)
      {
         messageArray[j][i] = convertLetterstoInt(message[count]);

      }

   }
   return messageArray;
}


int ** createDecrypterKey2D(int** oldKey)
{
   int **newArray = new int*[2];

   for (int i = 0; i < 2; ++i) {
      newArray[i] = new int[2];
   }

   int determinateMultiplierInverrse = 1;
   int determinate = determinateCalc(oldKey, 2);

   while (determinate < 0)
      determinate += 27;
   determinate %= 27;


   while ((determinate*determinateMultiplierInverrse) % 27 != 1)
      determinateMultiplierInverrse++;

   newArray[0][0] = oldKey[1][1];
   newArray[1][1] = oldKey[0][0];

   newArray[0][1] = -1 * oldKey[0][1];
   newArray[1][0] = -1 * oldKey[1][0];



   for (int i = 0; i < 2; i++)
   {
      for (int j = 0; j < 2; j++)
      {
         while (newArray[i][j] < 0)
            newArray[i][j] += 27;
         newArray[i][j] %= 27;
         newArray[i][j] *= determinateMultiplierInverrse;
         newArray[i][j] %= 27;
      }
   }
   return newArray;
}






string convertMatrixtoString(int ** matrix, int size, int length)
{
   string message = "";
   for (int i = 0; i < length; i++)
   {
      for (int j = 0; j < size; j++)
      {
         message += convertIntToChar(matrix[j][i]);


      }




   }




   return message;

}





int determinateCalc(int**array, int size)
{
   int count = 0;

   if (size == 2)
      return (array[0][0] * (array[1][1]) - (array[0][1] * (array[1][0])));
   else
   {
      //each column of array inouted
      for (int C = 0; C < size; C++)
      {
         int counter = 0;

         int **newArray = new int*[size - 1];
         //creates new array 
         for (int i = 0; i < size - 1; ++i) {
            newArray[i] = new int[size - 1];
         }
         //builds smaller array
         for (int r = 0; r < size; r++)
         {
            for (int c = 0; c < size; c++)
            {
               if ((r == 0) || (c == C))
                  int k = 0;
               else
               {
                  newArray[counter / (size - 1)][counter % (size - 1)] = array[r][c];
                  counter++;
               }
            }
         }
         count += pow(-1, C) * array[0][C] * (determinateCalc(newArray, size - 1));
         for (int i = 0; i < size - 1; i++)
            delete[] newArray[i];

         delete[] newArray;
      }
   }
   return  count;
}















bool checkForInvertibility(int**array, int size)
{


   if (determinateCalc(array, size) == 0)
      return false;
   else
      return true;



}



double ** invertMatrices(double **array, int sizeM, int sizeN)
{



   double **message = new double*[sizeM];

   for (int i = 0; i < sizeM; ++i) {
      message[i] = new double[sizeN];
   }

   //copying array into message
   for (int i = 0; i < sizeM; i++)
   {
      for (int j = 0; j < sizeN; j++)
         message[i][j] = array[i][j];
   }


   //creating and building identity matrix
   double **identityMatrix = new double*[sizeM];

   for (int i = 0; i < sizeM; ++i) {
      identityMatrix[i] = new double[sizeN];
   }


   for (int i = 0; i < sizeM; i++)
   {
      for (int j = 0; j < (sizeN); j++)
      {
         if ((i + 1) / (j + 1.0) == 1)
            identityMatrix[i][j] = 1;
         else
            identityMatrix[i][j] = 0;
      }
   }




   int rowsThrough = 0;

   while (rowsThrough < sizeM)
   {
      float multiplier;
      float divisor;

      for (int i = 0; i < sizeM; i++)
      {
         multiplier = message[i][rowsThrough] / (message[rowsThrough][rowsThrough]);
         divisor = message[rowsThrough][rowsThrough];

         for (int j = 0; j < sizeN; j++)
         {
            if (i == rowsThrough)
            {
               message[i][j] /= divisor;
               identityMatrix[i][j] /= divisor;
            }
            else
            {
               message[i][j] -= message[rowsThrough][j] * multiplier;
               identityMatrix[i][j] -= identityMatrix[rowsThrough][j] * multiplier;

            }
         }



      }
      rowsThrough++;
      //I need to add a check that makes sure the matrix is valid
   }

   return identityMatrix;
}







char convertIntToChar(int letter)
{
   switch (letter)
   {
   case 1:
      return 'A';
      break;
   case 2:
      return 'B';
      break;
   case 3:
      return 'C';
      break;
   case 4:
      return 'D';
      break;
   case 5:
      return 'E';
      break;
   case 6:
      return 'F';
      break;
   case 7:
      return 'G';
      break;
   case 8:
      return 'H';
      break;
   case 9:
      return 'I';
      break;
   case 10:
      return  'J';
      break;
   case 11:
      return 'K';
      break;
   case 12:
      return 'L';
      break;
   case 13:
      return 'M';
      break;
   case 14:
      return 'N';
      break;
   case 15:
      return 'O';
      break;
   case 16:
      return 'P';
      break;
   case 17:
      return 'Q';
      break;
   case 18:
      return 'R';
      break;
   case 19:
      return 'S';
      break;
   case 20:
      return 'T';
      break;
   case 21:
      return 'U';
      break;
   case 22:
      return 'V';
      break;
   case 23:
      return 'W';
      break;
   case 24:
      return 'X';
      break;
   case 25:
      return 'Y';
      break;
   case 0:
      return 'Z';
      break;
   default:
      return '_';
   }
}


int convertLetterstoInt(char letter)
{
   switch (letter)
   {
   case 'z':
      return 0;
      break;
   case 'a':
      return 1;
      break;
   case 'b':
      return 2;
      break;
   case 'c':
      return 3;
      break;
   case 'd':
      return 4;
      break;
   case 'e':
      return 5;
      break;
   case 'f':
      return 6;
      break;
   case 'g':
      return 7;
      break;
   case 'h':
      return 8;
      break;
   case 'i':
      return 9;
      break;
   case 'j':
      return  10;
      break;
   case 'k':
      return 11;
      break;
   case 'l':
      return 12;
      break;
   case 'm':
      return 13;
      break;
   case 'n':
      return 14;
      break;
   case 'o':
      return 15;
      break;
   case 'p':
      return 16;
      break;
   case 'q':
      return 17;
      break;
   case 'r':
      return 18;
      break;
   case 's':
      return 19;
      break;
   case 't':
      return 20;
      break;
   case 'u':
      return 21;
      break;
   case 'v':
      return 22;
      break;
   case 'w':
      return 23;
      break;
   case 'x':
      return 24;
      break;
   case 'y':
      return 25;
      break;
   case 'Z':
      return 0;
      break;
   case 'A':
      return 1;
      break;
   case 'B':
      return 2;
      break;
   case 'C':
      return 3;
      break;
   case 'D':
      return 4;
      break;
   case 'E':
      return 5;
      break;
   case 'F':
      return 6;
      break;
   case 'G':
      return 7;
      break;
   case 'H':
      return 8;
      break;
   case 'I':
      return 9;
      break;
   case 'J':
      return  10;
      break;
   case 'K':
      return 11;
      break;
   case 'L':
      return 12;
      break;
   case 'M':
      return 13;
      break;
   case 'N':
      return 14;
      break;
   case 'O':
      return 15;
      break;
   case 'P':
      return 16;
      break;
   case 'Q':
      return 17;
      break;
   case 'R':
      return 18;
      break;
   case 'S':
      return 19;
      break;
   case 'T':
      return 20;
      break;
   case 'U':
      return 21;
      break;
   case 'V':
      return 22;
      break;
   case 'W':
      return 23;
      break;
   case 'X':
      return 24;
      break;
   case 'Y':
      return 25;
      break;

   default:
      return 26;
   }
}




int **keyCreator(int size)
{
   int temp;


   int** keyArray = new int*[size];
   for (int i = 0; i < size; i++)
   {
      keyArray[i] = new int[size];
   }

   int tempSize = 0;
   cout << "Please enter each digit of the key startinggoing across the first row and then going down. " << endl << endl;
   for (int i = 0; i < size; i++)
   {

      for (int j = 0; j < size; j++)
      {
         cin >> temp;
         keyArray[i][j] = temp;
         tempSize++;
         cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;

         //outputs whats been read in already
         int moreTempSize = 0;
         while (moreTempSize < tempSize)
         {
            int a = moreTempSize / size;
            int b = moreTempSize % size;
            cout << setw(size) << keyArray[a][b];

            if (moreTempSize % size != size - 1)
            {
               cout << " | ";
            }






            if ((moreTempSize%size == size - 1) && ((moreTempSize / size) + 1 != size))
            {
               cout << endl;
               for (int s = 0; s < size * (size + 3); s++)
               {
                  cout << "_";
               }
               cout << endl;
               cout << endl;
            }





            moreTempSize++;
         }


      }
      cout << endl << endl;

   }








   return keyArray;
}



void printArray(int **& array, int m, int n)
{

   int tempSize = m * n;
   int moreTempSize = 0;
   while (moreTempSize < tempSize)
   {
      int a = moreTempSize / n;
      int b = moreTempSize % n;
      cout << setw(4) << array[a][b];

      if (moreTempSize % n != n - 1)
      {
         cout << " | ";
      }

      if ((moreTempSize%n == n - 1) && (moreTempSize != tempSize - 1))
      {
         cout << endl;
         for (int s = 0; s < n * 7; s++)
         {
            cout << "_";
         }
         cout << endl;
         cout << endl;
      }

      moreTempSize++;

   }
}


bool isInt(double num) {
   double absolute = abs(num);
   return absolute == floor(absolute);
}
