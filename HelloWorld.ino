
#define CS 2 // LCD Pin 4
#define SID 1 // 5
#define CLK 0 // 6

unsigned char Number[]={"0123456789"};
void Delay( unsigned char DelayTimm );
void SendSerialBit( unsigned char SendData );
void WriteCommand( unsigned char Command );
void WriteData( unsigned char Data );
void LcdDisplaySentence( unsigned char Address,unsigned char *Sentence );
void LcdDisplayHeadWord( unsigned char Address,unsigned char *HeadWord );
void LcdDisplayNextWord( unsigned char *NextWord );
void LcdInitial( void );

void setup() {
  pinMode(CS, OUTPUT);
  pinMode(SID, OUTPUT);
  pinMode(CLK, OUTPUT);
  LcdInitial( );
  LcdDisplaySentence( 0x80,"LCD Display Test" );
  LcdDisplayHeadWord( 0x90, &Number[0] );
  unsigned char Temp;
  for( Temp=1; Temp<10; Temp++ )
    LcdDisplayNextWord( &Number[Temp] );
  LcdDisplaySentence( 0x98,"Line 4" );
  LcdDisplaySentence( 0x88,"Line 3" );
}

void loop() {

}

void Delay( unsigned char DelayTime )
{
 while( DelayTime-- ); 
}
void SendSerialBit( unsigned char SendData )
{
  unsigned char i;
  for(i=0;i<8;i++)
  {
    if((SendData)&0x80)
      digitalWrite(SID, HIGH);
    else
      digitalWrite(SID, LOW);
    digitalWrite(CLK, HIGH);
    Delay(2);
    digitalWrite(CLK, LOW);
    SendData <<= 1;
  }
}
void WriteCommand( unsigned char Command )
{
 SendSerialBit( 0xf8 );
 SendSerialBit( Command & 0xf0 );
 SendSerialBit( Command << 4 );
 Delay( 10 );
}
void WriteData( unsigned char Data )
{
 SendSerialBit( 0xfa );
 SendSerialBit( Data & 0xf0 );
 SendSerialBit( Data << 4 );
 Delay( 10 );
}
void LcdDisplaySentence( unsigned char addr,const char *Sentence )
{
 unsigned char Length, i;
 WriteCommand( addr );
 Length = strlen( Sentence );
 for( i=0; i < Length; i++ )
   WriteData( *(Sentence + i) );
}
void LcdDisplayHeadWord( unsigned char addres,unsigned char *HeadWord )
{
 WriteCommand( addres );
 Delay( 10 ); 
 WriteData( *HeadWord );
}
void LcdDisplayNextWord( unsigned char *NextWord )
{
 WriteData( *NextWord );
}

void LcdInitial(void)
{
 Delay( 100 ); // Delay 100 us
 digitalWrite(CS, HIGH);
 WriteCommand( 0x30 ); // 8 bit Expand Instruction
 Delay( 100 );
 WriteCommand( 0x0C ); // Display ON
 Delay( 100 );
 WriteCommand( 0x01 ); // Clear Screen
 Delay( 100 );
 WriteCommand( 0x06 ); // Cursor Right Shift
 Delay( 100 );
 WriteCommand( 0x06 ); // Cursor Right Shift
 Delay( 100 );
}
// END 

