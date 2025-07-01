# Working with the SCDateTime Variables and Values

* [Introduction](#introduction)
* [SCDateTime Variables](#scdatetimevariables)
* [SCDateTimeMS Variables](#scdatetimemillisecondvariables)
* [Date Values](#datevalue)
* [Time Values](#timevalue)
* [Valid Ranges](#validranges)
* [SCDateTime Member Functions](#scdatetimememberfunctions)
  + [GetAsDouble()](#scdatetimemembergetasdouble)
  + [GetDate()](#scdatetimemembergetdate)
  + [GetDateTimeYMDHMS()](#scdatetimemembergetdatetimeymdhms)
  + [GetDateTimeYMDHMS\_MS()](#scdatetimemembergetdatetimeymdhmsms)
  + [GetDateYMD()](#scdatetimemembergetdateymd)
  + [GetDay()](#scdatetimemembergetday)
  + [GetDayOfWeek()](#scdatetimemembergetdayofweek)
  + [GetTimeHMS()](#scdatetimemembergettimehms)
  + [GetHour()](#scdatetimemembergethour)
  + [GetMicroSecond()](#scdatetimemembergetmicrosecond)
  + [GetMillisecond()](#scdatetimemembergetmillisecond)
  + [GetMinute()](#scdatetimemembergetminute)
  + [GetMonth()](#scdatetimemembergetmonth)
  + [GetSecond()](#scdatetimemembergetsecond)
  + [GetTimeInMilliseconds()](#scdatetimemembergettimeinmilliseconds)
  + [GetTimeInSeconds()](#scdatetimemembergettimeinseconds)
  + [GetTimeAsSCDateTime()](#scdatetimemembergettimeasscdatetime)
  + [GetTimeInSecondsWithoutMilliseconds()](#scdatetimemembergettimeinsecondswithoutmilliseconds)
  + [GetYear()](#scdatetimemembergetyear)
  + [IsSaturday()](#scdatetimememberissaturday)
  + [IsSunday()](#scdatetimememberissunday)
  + [IsWeekend()](#scdatetimememberisweekend)
  + [RoundDateTimeDownToMilliSecond()](#scdatetimememberrounddatetimedowntomillisecond)
  + [RoundDateTimeDownToMinute()](#scdatetimememberrounddatetimedowntominute)
  + [RoundDateTimeDownToSecond()](#scdatetimememberrounddatetimedowntosecond)
  + [RoundToNearestMilliSecond()](#scdatetimememberroundtonearestmillisecond)
  + [RoundToNearestSecond()](#scdatetimememberroundtonearestsecond)
  + [SCDateTime() Constructors](#scdatetimememberscdatetime)
  + [SetDate()](#scdatetimemembersetdate)
  + [SetDateTime()](#scdatetimemembersetdatetime)
  + [SetDateTimeYMDHMS()](#scdatetimemembersetdatetimeymdhms)
  + [SetDateTimeYMDHMS\_MS()](#scdatetimemembersetdatetimeymdhmsms)
  + [SetDateYMD()](#scdatetimemembersetdateymd)
  + [SetTime()](#scdatetimemembersettime)
  + [SetTimeHMS()](#scdatetimemembersettimehms)
  + [SetTimeHMS\_MS()](#scdatetimemembersettimehmsms)
  + [DAYS()](#scdatetimememberdays)
  + [YEARS()](#scdatetimememberyears)
  + [HOURS()](#scdatetimememberhours)
  + [MINUTES()](#scdatetimememberminutes)
  + [SECONDS()](#scdatetimememberseconds)
  + [MILLISECONDS()](#scdatetimemembermilliseconds)
  + [operator+=()](#scdatetimememberoperator)
  + [operator-=()](#scdatetimememberoperator)
* [Date and Time Functions](#dateandtimefunctions)
  + [DaysInDateSpanNotIncludingWeekends()](#daysindatespannotincludingweekends)
* [Working With SCDateTime Arrays](#scdatetimearrays)
* [DateAt()](#dateat)
* [TimeAt()](#timeat)
* [SetDateAt()](#setdateat)
* [SetTimeAt()](#settimeat)
* [Using References](#references)
* [Date and Time Math](#datetimemath)

---

## Introduction

[Link](#introduction) - [Top](#top)

The **SCDateTime** data type is used for Date-Time values in the ACSIL ([Advanced Custom Study Interface and Language](AdvancedCustomStudyInterfaceAndLanguage.md)).

The internal representation of Date-Time values in this data type is exactly the same as the Date-Time values used in Microsoft Excel and Libre Office Calc.

There are various independent global functions and member functions of the **SCDateTime** type which makes it easy to work with these values. This page documents these functions.

## SCDateTime Variables

[Link](#scdatetimevariables) - [Top](#top)

A **SCDateTime** variable contains a Date and Time value as a 64-bit integer. The external interface of **SCDateTime**.

The [ACSIL](AdvancedCustomStudyInterfaceAndLanguage.md) arrays [sc.BaseDateTimeIn](ACSIL_Members_Variables_And_Arrays.md#scbasedatetimein)[] and [sc.DateTimeOut](ACSIL_Members_Variables_And_Arrays.md#scdatetimeout)[] are of the SCDateTime type.

A SCDateTime variable can be locally defined within an ACSIL study function.

Refer to the examples given below.

Throughout the documentation and examples you will see the variable, **SCDateTimeVariable** being used. These variables are of the **SCDateTime** type.

The following operators are supported with SCDateTime variables: **= , += , -= , == , != ,< , <= , > , >=**.

A [SCDateTime](#scdatetimevariables) variable contains a number which represents a Date and Time. The Date is represented by the integer portion of this number and the Time is represented by the fractional portion of the number.

#### Example Code

```cpp

SCDateTime MySCDateTime; //Locally defined SCDateTime variable.

//MySCDateTime will contain, with this function call, the specified date time.
MySCDateTime.SetDateTimeYMDHMS(2007, 1, 30, 16, 10, 0);

int Hour, Minute, Second;
sc.BaseDateTimeIn[].GetTimeHMS(Hour, Minute, Second);

sc.DateTimeOut[DestinationIndex] = sc.BaseDateTimeIn[SourceIndex];
            
```

## SCDateTimeMS Variables

[Link](#scdatetimemillisecondvariables) - [Top](#top)

A **SCDateTimeMS** variable contains a Date and Time value as a 64-bit integer. It is identical to and supports the same member functions as [SCDateTime Variables](#scdatetimevariables).

SCDateTimeMS variables can be assigned to persistent variables by using the [sc.GetPersistentSCDateTime](ACSIL_Members_Functions.md#scgetpersistentscdatetime) and [sc.SetPersistentSCDateTime](ACSIL_Members_Functions.md#scsetpersistentscdatetime) functions.

As of version 2196, the **SCDateTime** and **SCDateTimeMS** Date-Time classes used within ACSIL and Sierra Chart are now exactly the same. SCDateTime now functions exactly like SCDateTimeMS where when comparisons are done, they are done to the microsecond rather than to the second. And there is no longer any internal rounding to the nearest second in **SCDateTime** for functions which would previously do this like **SCDateTime::GetTime**.

Instead the **GetTime** function will simply remove any microseconds component and just return number of seconds since midnight. Whereas previously **SCDateTime** would round to the nearest second.

## Date Values

[Link](#datevalue) - [Top](#top)

Date values are integer (**int**) values representing the number of days since December 30, 1899.

You can get a Date Value from a SCDateTime variable by using the [GetDate()](#scdatetimemembergetdate) member function.

You can set the date part of a SCDateTime variable by using the [SetDate()](#scdatetimemembersetdate) member function. Or by constructing a SCDateTime and specifying the date value for the first parameter and 0 for the second parameter (time value). Example: **SCDateTime DateVariable(DateValue, 0);**.

You can construct a Date Value from Year, Month, Day components by using the [SetDateYMD()](#scdatetimemembersetdateymd) function on a SCDateTime variable, and deconstruct a Date Value using the [GetDateYMD()](#scdatetimemembergetdateymd) function on a SCDateTime variable.

## Time Values

[Link](#timevalue) - [Top](#top)

Time Values are integer (**int**) values representing the number of seconds since midnight (00:00).

You can get a Time Value from a SCDateTime variable by using the [GetTimeInSeconds()](#scdatetimemembergettimeinseconds) member function.

You can set the time part of a SCDateTime variable from an integer time value by using the [SetTime()](#scdatetimemembersettime) member function. Or by constructing a SCDateTime and specifying 0 for the first parameter (date value) and the time value for the second parameter. Example: **SCDateTime DateVariable(0, 720);**. 720 means 720 seconds from midnight.

You can construct a Time Value from Hour, Minute, Second, Millisecond components by using the [SCDateTime::SetTimeHMS\_MS()](#scdatetimemembersettimehmsms) function, and get the individual Time Value components by using the [SCDateTime::GetTimeHMS()](#scdatetimemembergettimehms) function.

To compare the time components of two different SCDateTime variables with precision to the second, get the time values from them by using the [GetTimeInSeconds()](#scdatetimemembergettimeinseconds) function and compare those time values.

The *internal time value* of an SCDateTime can represent milliseconds/microseconds. There are corresponding member functions for these.

## Valid Ranges

[Link](#validranges) - [Top](#top)

The valid ranges for the Date and Time components in a SCDateTime variable are:

* **Year**: Four digit year. Example: 2012.
* **Month**: 1 through 12.
* **Day**: 1 through [days in month].
* **Hour**: 0 through 23.
* **Minute**: 0 through 59.
* **Second**: 0 through 59.
* **Millisecond**: 0 through 999.
* **Microsecond**: 0 through 999. (Currently used only as a counter for trades within the same millisecond. Does not represent actual microseconds.)

## SCDateTime Member Functions

[Link](#scdatetimememberfunctions) - [Top](#top)

### GetAsDouble()

[Link](#scdatetimemembergetasdouble) - [Top](#top)

Type: SCDateTime member function.

double **GetAsDouble**();

**GetAsDouble()** returns the internal Date-Time value as a double precision floating point value. This can be used to store the value externally.

This double precision floating point value can be passed to the SCDateTime constructor to create a new SCDateTime from it.

For a complete explanation of the Date component of this value, refer to [Date Value](SCDateTime.md#datevalue). The date value is the integer portion of the double. The fractional portion is the Time value which is represented as a fraction of one day where 1/86400000 is 1 millisecond. 86400000 is the number of milliseconds in a day.

#### Example Code

```cpp

const double DateTimeDouble = SCDateTimeVariable.GetAsDouble();
            
```

### GetDate()

[Link](#scdatetimemembergetdate) - [Top](#top)

Type: SCDateTime member function.

int **GetDate**();

**GetDate()** returns the date part of the SCDateTime variable. The value returned is a [Date Value](#datevalue).

#### Example Code

```cpp

int Date = SCDateTimeVariable.GetDate();
            
```

### GetDateTimeYMDHMS()

[Link](#scdatetimemembergetdatetimeymdhms) - [Top](#top)

Type: SCDateTime member function

void **GetDateTimeYMDHMS**(int& **Year**, int& **Month**, int& **Day**, int& **Hour**, int& **Minute**, int& **Second**);

**GetDateTimeYMDHMS()** gets the **Year**, **Month**, **Day**, **Hour**, **Minute**, and **Second** components of the SCDateTime variable. The function will set the **Year**, **Month**, **Day**, **Hour**, **Minute**, and **Second** variables provided as parameters.

Refer to the [Valid Ranges](#validranges) section for the range of values returned.

#### Example Code

```cpp

int Year, Month, Day, Hour, Minute, Second;

SCDateTimeVariable.GetDateTimeYMDHMS(Year, Month, Day, Hour, Minute, Second);
            
```

### GetDateTimeYMDHMS\_MS()

[Link](#scdatetimemembergetdatetimeymdhmsms) - [Top](#top)

Type: SCDateTime member function

void **GetDateTimeYMDHMS\_MS**(int& **Year**, int& **Month**, int& **Day**, int& **Hour**, int& **Minute**, int& **Second**, int& **MilliSecond**);

**GetDateTimeYMDHMS\_MS()** gets the year, month, day, hour, minute, second, and millisecond components of the SCDateTime variable. The function will set the **Year**, **Month**, **Day**, **Hour**, **Minute**, **Second**, and **MilliSecond** variables provided as parameters.

Refer to the [Valid Ranges](#validranges) section for the range of values returned.

#### Example Code

```cpp

int Year, Month, Day, Hour, Minute, Second, MilliSecond;

SCDateTimeVariable.GetDateTimeYMDHMS_MS(Year, Month, Day, Hour, Minute, Second, MilliSecond);
            
```

### GetDateYMD()

[Link](#scdatetimemembergetdateymd) - [Top](#top)

Type: SCDateTime member function

void **GetDateYMD**(int& **Year**, int& **Month**, int& **Day**);

**GetDateYMD()** gets the year, month, and day components of the SCDateTime variable.

The function will set the **Year**, **Month**, and **Day** variables provided as parameters.

Refer to the [Valid Ranges](#validranges) section for the range of values returned.

#### Example Code

```cpp

int Year = 0;
int Month = 0;
int Day = 0;            
SCDateTimeVariable.GetDateYMD(Year, Month, Day);
            
```

### GetDay()

[Link](#scdatetimemembergetday) - [Top](#top)

Type: SCDateTime member function

int **GetDay**();

**GetDay()** returns an integer value representing the day of the SCDateTime variable.

Refer to the [Valid Ranges](#validranges) section for the range of values returned.

#### Example Code

```cpp

int Day = sc.BaseDateTimeIn[sc.Index].GetDay();     
            
```

### GetDayOfWeek()

[Link](#scdatetimemembergetdayofweek) - [Top](#top)

Type: SCDateTime member function

int **GetDayOfWeek**();

The **GetDayOfWeek()** function returns the day of the week for the SCDateTime variable.

The return value will be one of the following:

* SUNDAY
* MONDAY
* TUESDAY
* WEDNESDAY
* THURSDAY
* FRIDAY
* SATURDAY

#### Example Code

```cpp

if (SCDateTimeVariable.GetDayOfWeek() == MONDAY)
{
    // SCDateTimeVariable is a Monday
}
            
```

### GetTimeHMS()

[Link](#scdatetimemembergettimehms) - [Top](#top)

Type: SCDateTime member function

int **GetTimeHMS**(int& **Hour**, int& **Minute**, int& **Second**);

**sc.GetTimeHMS()** gets the **Hour**, **Minute**, and **Second** components of the internal [Time Value](#timevalue) of the SCDateTime variable.

Refer to the [Valid Ranges](#validranges) section for the range of values returned.

#### Example Code

```cpp

int Hour = 0;
int Minute = 0;
int Second = 0;

SCDateTimeVariable.GetTimeHMS(Hour, Minute, Second);
            
```

### GetHour()

[Link](#scdatetimemembergethour) - [Top](#top)

Type: SCDateTime member function

int **GetHour**();

**GetHour()** returns an integer value representing the hour of the SCDateTime variable.

Refer to the [Valid Ranges](#validranges) section for the range of values returned.

#### Example Code

```cpp

int Hour = sc.BaseDateTimeIn[sc.Index].GetHour();
            
```

### GetMicroSecond()

[Link](#scdatetimemembergetmicrosecond) - [Top](#top)

Type: SCDateTime member function

int **GetMicroSecond**();

**GetMicroSecond()** returns an integer value representing the microsecond of the SCDateTime variable.

Refer to the [Valid Ranges](#validranges) section for the range of values returned.

#### Example Code

```cpp

int MicroSecond = sc.BaseDateTimeIn[sc.Index].GetMicroSecond();
            
```

### GetMillisecond()

[Link](#scdatetimemembergetmillisecond) - [Top](#top)

Type: SCDateTime member function

int **GetMillisecond**();

**GetMillisecond()** returns the milliseconds portion of the Date-Time variable.

Refer to the [Valid Ranges](#validranges) section for the range of values returned.

#### Example Code

```cpp

int MilliSecond = sc.BaseDateTimeIn[sc.Index].GetMillisecond();
            
```

### GetMinute()

[Link](#scdatetimemembergetminute) - [Top](#top)

Type: SCDateTime member function

int **GetMinute**();

**GetMinute()** returns an integer value representing the minute of the SCDateTime variable.

Refer to the [Valid Ranges](#validranges) section for the range of values returned.

#### Example Code

```cpp

int Minute = sc.BaseDateTimeIn[sc.Index].GetMinute();
            
```

### GetMonth()

[Link](#scdatetimemembergetmonth) - [Top](#top)

Type: SCDateTime member function

int **GetMonth**();

**GetMonth()** returns an integer value representing the month of the SCDateTime variable.

Refer to the [Valid Ranges](#validranges) section for the range of values returned.

#### Example Code

```cpp

int Month = sc.BaseDateTimeIn[sc.Index].GetMonth();       
            
```

### GetSecond()

[Link](#scdatetimemembergetsecond) - [Top](#top)

Type: SCDateTime member function

int **GetSecond**();

**GetSecond()** returns an integer value representing the second of the SCDateTime variable.

Refer to the [Valid Ranges](#validranges) section for the range of values returned.

#### Example Code

```cpp

int Second = sc.BaseDateTimeIn[sc.Index].GetSecond();
            
```

### GetTimeInMilliseconds()

[Link](#scdatetimemembergettimeinmilliseconds) - [Top](#top)

Type: SCDateTime member function

int **GetTimeInMilliseconds**();

**GetTimeInMilliseconds()** returns the time part of the SCDateTime variable in milliseconds since midnight.

The internal time value is rounded to the nearest millisecond if it contains microseconds.

#### Example Code

```cpp

int TimeInMilliseconds = SCDateTimeVariable.GetTimeInMilliseconds();
            
```

### GetTimeInSeconds()

[Link](#scdatetimemembergettimeinseconds) - [Top](#top)

Type: SCDateTime member function

int **GetTimeInSeconds**();

**GetTimeInSeconds()** returns the time part of the SCDateTime variable in seconds. The value returned is a [Time Value](#timevalue).

#### Example Code

```cpp

int TimeInSeconds = SCDateTimeVariable.GetTimeInSeconds();
            
```

### GetTimeAsSCDateTime()

[Link](#scdatetimemembergettimeasscdatetime) - [Top](#top)

Type: SCDateTime member function

SCDateTime **GetTimeAsSCDateTime**();

**GetTimeAsSCDateTime()** returns the time part of the SCDateTime variable. The value returned is a [SCDateTime variable](#scdatetimevariables).

#### Example Code

```cpp

SCDateTime TimeOnly = SCDateTimeVariable.GetTimeAsSCDateTime();
            
```

### GetTimeInSecondsWithoutMilliseconds()

[Link](#scdatetimemembergettimeinsecondswithoutmilliseconds) - [Top](#top)

Type: SCDateTime member function

int **GetTimeInSecondsWithoutMilliseconds**();

**GetTimeInSecondsWithoutMilliseconds()** returns the time part of the SCDateTime variable without the milliseconds part. The value returned is a [Time Value](#timevalue).

The millisecond/microsecond component is discarded so that the value is truncated to the containing second.

#### Example Code

```cpp

int Time = SCDateTimeVariable.GetTimeInSecondsWithoutMilliseconds();
            
```

### GetYear()

[Link](#scdatetimemembergetyear) - [Top](#top)

Type: SCDateTime member function

int **GetYear**();

**GetYear()** returns an integer value representing the year of the SCDateTime variable.

Refer to the [Valid Ranges](#validranges) section for the range of values returned.

#### Example Code

```cpp

int Year = sc.BaseDateTimeIn[sc.Index].GetYear();            
            
```

### IsSaturday()

[Link](#scdatetimememberissaturday) - [Top](#top)

Type: SCDateTime member function

int **IsSaturday**();

**IsSaturday()** returns an boolean value (true or false) depending on whether the day of the week for the SCDateTime variable is **SATURDAY**.

### IsSunday()

[Link](#scdatetimememberissunday) - [Top](#top)

Type: SCDateTime member function

int **IsSunday**();

**IsSunday()** returns an boolean value (true or false) depending on whether the day of the week for the SCDateTime variable is **SUNDAY**.

### IsWeekend()

[Link](#scdatetimememberisweekend) - [Top](#top)

Type: SCDateTime member function

int **IsWeekend**();

**IsWeekend()** returns an boolean value (true or false) depending on whether the day of the week for the SCDateTime variable is a weekend day (**SATURDAY** or **SUNDAY**).

### RoundDateTimeDownToMilliSecond()

[Link](#scdatetimememberrounddatetimedowntomillisecond) - [Top](#top)

Type: SCDateTime member function

void **RoundDateTimeDownToMilliSecond**();

The **RoundDateTimeDownToMilliSecond()** function rounds down the Date-Time value contained within the SCDateTime variable to the millisecond and removes the microseconds. Therefore, the microseconds will be zero.

#### Example Code

```cpp

SCDateTime BarDateTime = sc.BaseDateTimeIn[sc.Index];
BarDateTime.RoundDateTimeDownToMilliSecond();
            
```

### RoundDateTimeDownToMinute()

[Link](#scdatetimememberrounddatetimedowntominute) - [Top](#top)

Type: SCDateTime member function

void **RoundDateTimeDownToMinute**();

The **RoundDateTimeDownToMinute()** function rounds down the Date-Time value contained within the SCDateTime variable to the minute and removes the seconds. Therefore, the seconds will be zero.

#### Example Code

```cpp

SCDateTime BarDateTime = sc.BaseDateTimeIn[sc.Index];
BarDateTime.RoundDateTimeDownToMinute();
            
```

### RoundDateTimeDownToSecond()

[Link](#scdatetimememberrounddatetimedowntosecond) - [Top](#top)

Type: SCDateTime member function

void **RoundDateTimeDownToSecond**();

The **RoundDateTimeDownToSecond()** function rounds down the Date-Time value contained within the SCDateTime variable to the second and removes the milliseconds. Therefore, the milliseconds will be zero.

#### Example Code

```cpp

SCDateTime BarDateTime = sc.BaseDateTimeIn[sc.Index];
BarDateTime.RoundDateTimeDownToSecond();
            
```

### RoundToNearestMilliSecond()

[Link](#scdatetimememberroundtonearestmillisecond) - [Top](#top)

Type: SCDateTime member function

void **RoundToNearestMilliSecond**();

The **RoundToNearestMilliSecond()** function rounds the Date-Time value contained within the SCDateTime variable to the nearest millisecond and removes the microseconds. Therefore, the microseconds will be zero.

#### Example Code

```cpp

SCDateTime BarDateTime = sc.BaseDateTimeIn[sc.Index];
BarDateTime.RoundToNearestMilliSecond();
            
```

### RoundToNearestSecond()

[Link](#scdatetimememberroundtonearestsecond) - [Top](#top)

Type: SCDateTime member function

void **RoundToNearestSecond**();

The **RoundToNearestSecond()** function rounds the Date-Time value contained within the SCDateTime variable to the nearest second and removes the milliseconds. Therefore, the milliseconds will be zero.

#### Example Code

```cpp

SCDateTime BarDateTime = sc.BaseDateTimeIn[sc.Index];
BarDateTime.RoundToNearestSecond();
            
```

### SCDateTime() Constructors

[Link](#scdatetimememberscdatetime) - [Top](#top)

Type: SCDateTime constructor.

**SCDateTime**();

**SCDateTime**(double **DateTime** );

**SCDateTime**(const [SCDateTime](#scdatetimevariables) & **DateTime**);

**SCDateTime**(int [DateValue](#datevalue), int [TimeValue](#timevalue));

**SCDateTime**(int **Hour**, int **Minute**, int **Second**, int **Millisecond**);

**SCDateTime**(int **Year**, int **Month**, int **Day**, int **Hour**, int **Minute**, int **Second**);

**SCDateTime()** is the constructor function that constructs and initializes a SCDateTime variable. Using the different constructors, it is supported to assign the Year, Month, Day, Hour, Minute, Second, Millisecond values to the SCDateTime variable. Or a [Date Value](#datevalue) or [Time Value](#timevalue).

Refer to the [Valid Ranges](#validranges) section for valid values that can be used for the parameters.

#### Example Code

```cpp

SCDateTime DateTime(2017, 1, 30, 0, 0, 0);
SCDateTime DateTime(2012, 1, 1, 12, 0, 0);
            
```

### SetDate()

[Link](#scdatetimemembersetdate) - [Top](#top)

Type: SCDateTime member function

SCDateTime& **SetDate**(int **Date**);

**SetDate()** sets the date part of the SCDateTime variable with the given **Date**. **Date** must be given as a [Date Value](#datevalue).

The existing time portion of the SCDateTime variable is preserved when using the **SetDate()**function.

#### Example Code

```cpp

SCDateTime SCDateTimeVariable;
SCDateTimeVariable.SetDate(sc.BaseDateTimeIn[sc.Index].GetDate());
            
```

### SetDateTime()

[Link](#scdatetimemembersetdatetime) - [Top](#top)

Type: SCDateTime member function

int **SetDateTime**(int **Date**, int **Time**);

**SetDateTime()** sets the SCDateTime variable with the given **Date** and **Time** components. **Date** must be given as a [Date Value](#datevalue), and **Time** must be given as a [Time Value](#timevalue).

#### Example Code

```cpp

r_StopDateTime.SetDateTime(sc.BaseDateTimeIn[sc.Index].GetDate(), Input_StopTime.GetTime());
            
```

### SetDateTimeYMDHMS()

[Link](#scdatetimemembersetdatetimeymdhms) - [Top](#top)

Type: SCDateTime member function

SCDateTime& **SetDateTimeYMDHMS**(int **Year**, int **Month**, int **Day**, int **Hour**, int **Minute**, int **Second**);

**SetDateTimeYMDHMS()** sets the SCDateTime variable with the given **Year**, **Month**, **Day**, **Hour**, **Minute**, and **Second** components.

Refer to the [Valid Ranges](#validranges) section for valid values that can be used.

#### Example Code

```cpp

SCDateTimeVariable.SetDateTimeYMDHMS(2007, 1, 30, 16, 10, 0);
            
```

### SetDateTimeYMDHMS\_MS()

[Link](#scdatetimemembersetdatetimeymdhmsms) - [Top](#top)

Type: SCDateTime member function

SCDateTime& **SetDateTimeYMDHMS\_MS**(int **Year**, int **Month**, int **Day**, int **Hour**, int **Minute**, int **Second**, int **MilliSecond**);

**SetDateTimeYMDHMS\_MS()** sets the SCDateTime variable with the given **Year**, **Month**, **Day**, **Hour**, **Minute**, **Second**, and **MilliSecond** components.

Refer to the [Valid Ranges](#validranges) section for valid values that can be used.

#### Example Code

```cpp

SCDateTimeVariable.SetDateTimeYMDHMS_MS(2007, 1, 30, 16, 10, 0, 0);
            
```

### SetDateYMD()

[Link](#scdatetimemembersetdateymd) - [Top](#top)

Type: SCDateTime member function

SCDateTime& **SetDateYMD**(int **Year**, int **Month**, int **Day**);

**SetDateYMD()** sets the date part of the SCDateTime variable with the given **Year**, **Month**, and **Day** components.

Refer to the [Valid Ranges](#validranges) section for valid values that can be used.

#### Example Code

```cpp

SCDateTimeVariable.SetDateYMD(2007, 1, 30);
            
```

### SetTime()

[Link](#scdatetimemembersettime) - [Top](#top)

Type: SCDateTime member function

SCDateTime& **SetTime**(int **Time**);

The **SetTime()** function sets the time part, in seconds, of the SCDateTime variable with the given **Time**. **Time** must be given as a [Time Value](#timevalue).

The existing date portion of the SCDateTime variable is preserved when using the **SetTime()**function.

#### Example Code

```cpp

SCDateTime TimeValue(16, 14, 59, 0);//Construct a time value

SCDateTimeVariable.SetTime(TimeValue);
            
```

### SetTimeHMS()

[Link](#scdatetimemembersettimehms) - [Top](#top)

Type: SCDateTime member function

SCDateTime& **SetTimeHMS**(int **Hour**, int **Minute**, int **Second**);

**SetTimeHMS()** sets the time part of the SCDateTime variable with the given **Hour**, **Minute**, and **Second** components. The existing date in the variable is not changed and left as is.

Refer to the [Valid Ranges](#validranges) section for valid values that can be used.

#### Example Code

```cpp

SCDateTimeVariable.SetTimeHMS(16, 10, 0);
            
```

### SetTimeHMS\_MS()

[Link](#scdatetimemembersettimehmsms) - [Top](#top)

Type: SCDateTime member function

SCDateTime& **SetTimeHMS\_MS**(int **Hour**, int **Minute**, int **Second**, int **MilliSecond**);

**SetTimeHMS\_MS()** sets the time part of the SCDateTime variable with the given **Hour**, **Minute**, **Second**, and **MilliSecond** components. The existing date in the variable is not changed and left as is.

Refer to the [Valid Ranges](#validranges) section for valid values that can be used.

#### Example Code

```cpp

SCDateTimeVariable.SetTimeHMS_MS(16, 10, 0, 0);
            
```

### DAYS()

[Link](#scdatetimememberdays) - [Top](#top)

Type: SCDateTime static member function

static SCDateTime& **DAYS**(int **Days**);

The **DAYS()** static member function constructs and returns an SCDateTime variable containing the number of days according to the specified number of days.

#### Example Code

```cpp

SCDateTime DateTimeVariable;
DateTimeVariable += SCDateTime::DAYS(5);
            
```

### YEARS()

[Link](#scdatetimememberyears) - [Top](#top)

Type: SCDateTime static member function

static SCDateTime& **YEARS**(int **Years**);

The **YEARS()** static member function constructs and returns an SCDateTime variable containing the number of years according to the specified number of years.

#### Example Code

```cpp

SCDateTime DateTimeVariable;
DateTimeVariable += SCDateTime::YEARS(5);
            
```

### HOURS()

[Link](#scdatetimememberhours) - [Top](#top)

Type: SCDateTime static member function

static SCDateTime& **HOURS**(int **Hours**);

The **HOURS()** static member function constructs and returns an SCDateTime variable containing the number of hours according to the specified number of hours.

#### Example Code

```cpp

SCDateTime DateTimeVariable;
DateTimeVariable += SCDateTime::HOURS(5);
            
```

### MINUTES()

[Link](#scdatetimememberminutes) - [Top](#top)

Type: SCDateTime static member function

static SCDateTime& **MINUTES**(int **Minutes**);

The **MINUTES()** static member function constructs and returns an SCDateTime variable containing the number of minutes according to the specified number of minutes.

#### Example Code

```cpp

SCDateTime DateTimeVariable;
DateTimeVariable += SCDateTime::MINUTES(5);
            
```

### SECONDS()

[Link](#scdatetimememberseconds) - [Top](#top)

Type: SCDateTime static member function

static SCDateTime& **SECONDS**(int **Seconds**);

The **SECONDS()** static member function constructs and returns an SCDateTime variable containing the number of seconds according to the specified number of seconds.

#### Example Code

```cpp

SCDateTime DateTimeVariable;
DateTimeVariable += SCDateTime::SECONDS(5);
            
```

### MILLISECONDS()

[Link](#scdatetimemembermilliseconds) - [Top](#top)

Type: SCDateTime static member function

static SCDateTime& **MILLISECONDS**(int **Milliseconds**);

The **MILLISECONDS()** static member function constructs and returns an SCDateTime variable containing the number of milliseconds according to the specified number of milliseconds.

#### Example Code

```cpp

SCDateTime DateTimeVariable;
DateTimeVariable += SCDateTime::MILLISECONDS(5);
            
```

### operator+=()

[Link](#scdatetimememberoperator) - [Top](#top)

Type: SCDateTime member operator

const SCDateTime& **+=**(const SCDateTime& **DateTime**);

The **+=** member operator adds the given **DateTime** parameter to the existing Date-Time value in the SCDateTime object it is called in relation to.

The given **DateTime** parameter usually will represent a certain amount of time, like for example 1 hour, and not represent a particular absolute Date-Time.

#### Example Code

```cpp

SCDateTime DateTimeVariable;
DateTimeVariable += SCDateTime::YEARS(5);
            
```

### operator-=()

[Link](#scdatetimememberoperator) - [Top](#top)

Type: SCDateTime member operator

const SCDateTime& **-=**(const SCDateTime& **DateTime**);

The **-=** member operator subtracts the given **DateTime** parameter to the existing Date-Time value in the SCDateTime object it is called in relation to.

The given **DateTime** parameter usually will represent a certain amount of time, like for example 1 hour, and not represent a particular absolute Date-Time.

#### Example Code

```cpp

SCDateTime Time(1, 10, 0, 0); //1 Hour and 10 Minutes.
SCDateTime DateTimeVariable;
DateTimeVariable -= Time;
            
```

## Date and Time Functions

[Link](#dateandtimefunctions) - [Top](#top)

### DaysInDateSpanNotIncludingWeekends()

[Link](#daysindatespannotincludingweekends) - [Top](#top)

Type: Function

int **DaysInDateSpanNotIncludingWeekends**(int **FirstDate**, int **LastDate**)

The **DaysInDateSpanNotIncludingWeekends()** function calculates the number of days within the date span specified by the  **FirstDate**  and the **LastDate** parameters, not including Saturday and Sunday.

The calculation includes both of these dates as well. Both of these parameters are [Date Values](#datevalue).

#### Example Code

```cpp

int NumberOfDays = DaysInDateSpanNotIncludingWeekends(sc.BaseDateTimeIn[sc.Index - 100].GetDate(), sc.BaseDateTimeIn[sc.Index].GetDate());
            
```

## Working With SCDateTime Arrays

[Link](#scdatetimearrays) - [Top](#top)

When working with the [sc.BaseDateTimeIn[]](index49ba.html?page=doc/ACSIL_Members_Variables_And_Arrays.html#scBaseDateTimeIn) array, you can use different methods for getting the date and/or time parts from elements in the array. These methods are given below.

#### Using the **GetDate()** and **GetTimeInSeconds()** member functions of a **SCDateTime** variable

```cpp

// Get the date of the bar at the current index
int CurrentBarDate = sc.BaseDateTimeIn[sc.Index].GetDate();

// Get the time of the bar at the current index
int CurrentBarTime = sc.BaseDateTimeIn[sc.Index].GetTimeInSeconds();
        
```

#### Using the **DateAt()** and **TimeAt()** member functions of a **SCDateTime** array

```cpp

// Get the date of the bar at the current index
int CurrentBarDate = sc.BaseDateTimeIn.DateAt(sc.Index);

// Get the time of the bar at the current index
int CurrentBarTime = sc.BaseDateTimeIn.TimeAt(sc.Index);			
        
```

#### Using the **[]** array operator on the **sc.BaseDateTimeIn** SCDateTime array to get the Date and Time

```cpp

if (sc.BaseDateTimeIn[sc.Index] - sc.BaseDateTimeIn[sc.Index - 1] > SCDateTime::MINUTES(1))
{
	// The current bar being processed has a Date-Time which is more than one minute later than the prior bar Date-Time.
}			
        
```

### DateAt()

[Link](#dateat) - [Top](#top)

Type: SCDateTimeArray member function

int **DateAt**(int **Index**);

**DateAt()** returns the date part of the SCDateTime variable at the given **Index** in the SCDateTime array. The value returned is a [Date Value](#datevalue).

#### Example Code

```cpp

// Get the date at the current index
int Date = sc.BaseDateTimeIn.DateAt(sc.Index);
        
```

### TimeAt()

[Link](#timeat) - [Top](#top)

Type: SCDateTimeArray member function

int **TimeAt**(int **Index**);

**TimeAt()** returns the time part of the SCDateTime variable at the given **Index** in the SCDateTime array. The value returned is a [Time Value](#timevalue).

#### Example Code

```cpp

// Get the time at the current index
int Time = sc.BaseDateTimeIn.TimeAt(sc.Index);
        
```

### SetDateAt()

[Link](#setdateat) - [Top](#top)

Type: SCDateTimeArray member function

int **SetDateAt**(int **Index**, int **Date**);

**SetDateAt()** sets the date part of the DateTime variable at the given **Index** in the SCDateTime array. **Date** must be given as a [Date Value](#datevalue). The value returned is the same value that is passed in for **Date**. This function *must not* be used on the [sc.BaseDateTimeIn[]](index49ba.html?page=doc/ACSIL_Members_Variables_And_Arrays.html#scBaseDateTimeIn) array. The only array you'll probably ever use this on is the [sc.DateTimeOut[]](index49ba.html?page=doc/ACSIL_Members_Variables_And_Arrays.html#scDateTimeOut) array.

#### Example Code

```cpp

// Set the date for a custom chart bar
int Date = sc.DateTimeOut.SetDateAt(CustomIndex,sc.BaseDateTimeIn[sc.Index].GetDate());
        
```

### SetTimeAt()

[Link](#settimeat) - [Top](#top)

Type: SCDateTimeArray member function

int **SetTimeAt**(int **Index**, int **Time**);

**SetTimeAt()** sets the time part of the DateTime variable at the given **Index** in the SCDateTime array. **Time** must be given as a [Time Value](#timevalue). The value returned is the same value that is passed in for **Time**. This function *must not* be used on the [sc.BaseDateTimeIn[]](index49ba.html?page=doc/ACSIL_Members_Variables_And_Arrays.html#scBaseDateTimeIn) array. The only array you will need to use this on is the [sc.DateTimeOut[]](index49ba.html?page=doc/ACSIL_Members_Variables_And_Arrays.html#scDateTimeOut) array.

#### Example Code

```cpp

// Set the time for a custom chart bar
int Time = sc.DateTimeOut.SetTimeAt(CustomIndex,sc.BaseDateTimeIn[sc.Index].GetTimeInSeconds());
        
```

## Using References

[Link](#references) - [Top](#top)

The SCDateTime reference type, **SCDateTimeArrayRef**, can be used to set a reference to a **SCDateTimeArray** array to simplify writing code. See the example below.

#### Example Code

```cpp

SCDateTimeArrayRef DateTimes = sc.BaseDateTimeIn;
int Time;
Time = DateTimes[sc.Index].GetTimeInSeconds();
            
```

## Date and Time Math

[Link](#datetimemath) - [Top](#top)

[SCDateTime Variable Documentation](#scdatetimevariables)

#### Adding 30 seconds to a SCDateTime variable

```cpp

SCDateTimeVariable.AddSeconds(30);
            
```

#### Subtracting 5 minutes from a SCDateTime variable

```cpp

SCDateTimeVariable.SubtractMinutes(5);
            
```

#### Adding 1 hour to a SCDateTime variable

```cpp

SCDateTimeVariable.AddHours(1);
            
```

#### Adding 1 day to a SCDateTime variable

```cpp

SCDateTimeVariable.AddDays(1);
            
```

#### Adding 1 week to a SCDateTime variable

```cpp

SCDateTimeVariable.AddDays(DAYS_PER_WEEK);
            
```

#### Adding 1 year to a SCDateTime variable

```cpp

SCDateTimeVariable.AddYears(1);
            
```

---

\*Last modified Friday, 31st January, 2025.
