
SerialIO.list() @=> string list[];

for(int i; i < list.cap(); i++)
{
    chout <= i <= ": " <= list[i] <= IO.newline();
}

SerialIO cereal;
cereal.open(0, SerialIO.B9600, SerialIO.BINARY);

while(true)
{
    cereal.onBytes(4) => now;
    cereal.getBytes() @=> int bytes[];
    chout <= "bytes: ";
    for(int i; i < bytes.cap(); i++)
    {
        chout <= bytes[i] <= " ";
    }
    
    chout <= IO.newline();
}
