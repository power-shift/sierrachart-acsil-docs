# ACSIL Study Documentation Interface Members

* [Introduction](#intro)
* [Documentation Members](#documentationmembers)

---

## Introduction

[Link](#intro) - [Top](#top)

The following ACSIL (Advanced Custom Study Interface and Language) interface members on this page are used to document an Advanced Custom Study.

When a custom study is added by selecting **Analysis >> Studies >> Add Custom Study** **>> [Custom Study Name]**, the **Display Study Documentation** button can be pressed which will generate a HTML page that is opened in the Web browser which documents the study using the data you have set with the members documented here.

## Documentation Members

[Link](#documentationmembers) - [Top](#top)

### SCString sc.StudyDescription

The **sc.StudyDescription** text string can be set to the description you want for your study. It can contain HTML.

### sc.Input[].SetDescription(SCString InputDescription)

The **sc.Input[].SetDescription()** function takes a text string which sets a description for the specified sc.Input[]. It can contain HTML.

### SCString sc.DocumentationImageURL

The **sc.DocumentationImageURL** text string can be set to an internet URL specifying an image file which shows an example of the study output.

---

\*Last modified Thursday, 06th January, 2022.
