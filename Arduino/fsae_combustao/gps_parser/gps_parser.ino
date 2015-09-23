char globalString[100];//declare a global sufficiently large to hold you results


void loop()
{
    int chars = mySerial.available();
    int i;
    char *myString;
    if (chars>0)
    {
        myString = calloc(chars+1, sizeof(char));
        for(i=0;i<chars;i++)
        {
            myString[i] = mySerial.read();
            //test for EOF
            if((myString[i] == '\n') ||(myString[i] == '\r'))
            {
                //pick this...
                myString[i]=0;//strip carriage - return line feed(or skip)
                //OR pick this... (one or the other. i.e.,I do not know the requirements for your string)
                if(i<chars)
                {
                    myString[i+1] = mySerial.read() //get remaining '\r' or '\n'
                    myString[i+2]=0;//add null term if necessary
                }

                break;
            }
        }
        if(strstr(myString, "GPGGA") == NULL)
          {
               Serial.println("Not a GPGGA string");
               //EDIT
               strcpy(globalString, "");//if failed, do not want globalString populated
          }
          else
          {    //EDIT
               strcpy(globalString, myString);
          }

    }
    //free(myString) //somewhere when you are done with it
}
