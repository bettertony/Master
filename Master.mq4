//+------------------------------------------------------------------+
#property copyright "Copyright 2017, MetaQuotes Software Corp."
#property link      "https://www.mql5.com"
#property version   "1.00"
#property strict

#import "Master.dll"
void RateInfo(string);
#import
//+------------------------------------------------------------------+
void OnTick()
  {
   RateInfo("Hello!");
   return;
  }
//+------------------------------------------------------------------+
