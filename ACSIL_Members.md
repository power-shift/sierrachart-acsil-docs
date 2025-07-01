# ACSIL Interface Members - Introduction

## Related Documentation

* **ACSIL Interface Members - Introduction**
* [ACSIL Interface Members - Variables and Arrays](ACSIL_Members_Variables_And_Arrays.md)
* [ACSIL Interface Members - sc.Input Array](ACSIL_Members_scInputs.md)
* [ACSIL Interface Members - sc.Subgraph Array](ACSIL_Members_scSubgraph.md)
* [ACSIL Interface Members - Functions](ACSIL_Members_Functions.md)
* [ACSIL Interface Members - Graphics Functions](ACSIL_Members_GraphicsFunctions.md).

---

## ACSIL Interface Members - Introduction

The information on the pages linked to above applies to the Sierra Chart Advanced Custom Study Interface and Language (ACSIL). For complete information about the ACSIL, refer to [Advanced Custom Study Interface and Language](AdvancedCustomStudyInterfaceAndLanguage.md).

In the pages linked to above you will find all of the members of the Advanced Custom Study Interface available to your study function. These include variables, arrays, functions, and data structures. These members need to be prefixed with **sc.** when using them in your study function.

From time to time new interface members are added. If you use one of the members and receive a compiler error, then the possible cause is that you are not running the latest version of Sierra Chart. If a compiled Advanced Custom Study uses a member which is not supported in an older version of Sierra Chart that it is being used with, then when the study is used in that older version an error will be given in the Message Log indicating that a newer version is required.

An alternative method to access a sc.Subgraph[].Data array element is available. Example: **[sc.Subgraph](ACSIL_Members_scSubgraph.md#scsubgraph)[0][sc.Index]** is equivalent to **[sc.Subgraph](ACSIL_Members_scSubgraph.md#scsubgraph)[0].[Data](ACSIL_Members_scSubgraph.md#scsubgraphdata)[sc.Index]**. These two methods are used interchangeably in this documentation.

---

\*Last modified Sunday, 23rd February, 2025.
