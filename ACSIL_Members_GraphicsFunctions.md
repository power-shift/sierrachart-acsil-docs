# ACSIL Interface Members - Graphics Functions

## Related Documentation

* [ACSIL Interface Members - Introduction](ACSIL_Members.md).
* [ACSIL Interface Members - Variables and Arrays](ACSIL_Members_Variables_And_Arrays.md).
* [ACSIL Interface Members - sc.Input Array](ACSIL_Members_scInputs.md).
* [ACSIL Interface Members - sc.Subgraph Array](ACSIL_Members_scSubgraph.md).
* [ACSIL Interface Members - Functions](ACSIL_Members_Functions.md).
* **ACSIL Interface Members - Graphics Functions**

---

## On This Page

* [Notes About Graphics Functions](#notesaboutgraphicsfunctions).
* [sc.DrawFrameControl()](#scdrawframecontrol).
* [sc.DrawEdge()](#scdrawedge).
* [sc.GetCurrentPosition()](#scgetcurrentposition).
* [sc.LineTo()](#sclineto).
* [sc.MoveTo()](#scmoveto).
* [sc.SetPixel()](#scsetpixel).
* [sc.FillEllipse()](#scfillellipse).
* [sc.DrawEllipseOutline()](#scdrawellipseoutline).
* [sc.DrawEllipseWithRadius()](#scdrawellipsewithradius).
* [sc.DrawEllipse()](#scdrawellipse).
* [sc.DrawArc()](#scdrawarc).
* [sc.DrawTextWithState()](#scdrawtextwithstate).
* [sc.DrawTextInRectangle()](#scdrawtextinrectangle).
* [sc.DrawTextAt()](#scdrawtextat).
* [sc.DrawText()](#scdrawtext).
* [sc.Internal\_DrawPolygon()](#scinternaldrawpolygon).
* [sc.FillRectangleWithColor()](#scfillrectanglewithcolor).
* [sc.FillRectangle()](#scfillrectangle).
* [sc.Draw3DRectangle()](#scdraw3drectangle).
* [sc.DrawFocusRectangle()](#scdrawfocusrectangle).
* [sc.DrawRectangle()](#scdrawrectangle).
* [sc.GetTextSizeWithFont()](#scgettextsizewithfont).
* [sc.GetTextSize()](#scgettextsize).
* [sc.GetTextHeightWithFont()](#scgettextheightwithfont).
* [sc.GetTextHeight()](#scgettextheight).
* [sc.CalculateFontPointSize()](#sccalculatefontpointsize).
* [sc.CalculateFontLogicalHeight()](#sccalculatefontlogicalheight).
* [sc.GetDeviceCaps()](#scgetdevicecaps).
* [sc.ResetTextFont()](#scresettextfont).
* [sc.ResetTextColor()](#scresettextcolor).
* [sc.ResetTextAlign()](#scresettextalign).
* [sc.ResetPen()](#scresetpen).
* [sc.ResetBrush()](#scresetbrush).
* [sc.ResetMixMode()](#scresetmixmode).
* [sc.ResetClippingRegion()](#scresetclippingregion).
* [sc.ResetBackgroundMode()](#scresetbackgroundmode).
* [sc.ResetBackgroundColor()](#scresetbackgroundcolor).
* [sc.SetTextFont()](#scsettextfont).
* [sc.SetTextColor()](#scsettextcolor).
* [sc.SetTextAlign()](#scsettextalign).
* [sc.SetPen()](#scsetpen).
* [sc.SetBrush()](#scsetbrush).
* [sc.SetMixMode()](#scsetmixmode).
* [sc.SetClippingRegionFromRectangle()](#scsetclippingregionfromrectangle).
* [sc.SetBackgroundMode()](#scsetbackgroundmode).
* [sc.SetBackgroundColor()](#scsetbackgroundcolor).
* [sc.DrawPolygon()](#scdrawpolygon).

* [Common Function Parameter Descriptions](#commonfunctionparameterdescriptions).

---

## Functions

[Link](#functions) - [Top](#top)

### Notes About Graphics Functions

[Link](#notesaboutgraphicsfunctions) - [Top](#top)

### sc.DrawFrameControl()

[Link](#scdrawframecontrol) - [Top](#top)

**Type**: Function

int32\_t **DrawFrameControl**(n\_ACSIL::s\_GraphicsRectangle& **r\_Rectangle**, const uint32\_t **Type**, const uint32\_t **State**);

#### Parameters

* **r\_Rectangle**:
* **Type**:
* **State**:

#### Example

*No example provided by SierraChart*

### sc.DrawEdge()

[Link](#scdrawedge) - [Top](#top)

**Type**: Function

int32\_t **DrawEdge**(n\_ACSIL::s\_GraphicsRectangle& **r\_Rectangle**, const uint32\_t **EdgeType**, const uint32\_t **Flags**);

#### Parameters

* **r\_Rectangle**:
* **EdgeType**:
* **Flags**:

#### Example

*No example provided by SierraChart*

### sc.GetCurrentPosition()

[Link](#scgetcurrentposition) - [Top](#top)

**Type**: Function

int32\_t **GetCurrentPosition**(n\_ACSIL::s\_GraphicsPoint& **r\_GraphicsPoint**);

#### Parameters

* **r\_GraphicsPoint**:

#### Example

*No example provided by SierraChart*

### sc.LineTo()

[Link](#sclineto) - [Top](#top)

**Type**: Function

int32\_t **LineTo**(const int32\_t **XCoordinate**, const int32\_t **YCoordinate**);

#### Parameters

* **XCoordinate**:
* **YCoordinate**:

#### Example

*No example provided by SierraChart*

### sc.MoveTo()

[Link](#scmoveto) - [Top](#top)

**Type**: Function

int32\_t **MoveTo**(const int32\_t **XCoordinate**, const int32\_t **YCoordinate**);

#### Parameters

* **XCoordinate**:
* **YCoordinate**:

#### Example

*No example provided by SierraChart*

### sc.SetPixel()

[Link](#scsetpixel) - [Top](#top)

**Type**: Function

int32\_t **SetPixel**(const int32\_t **XCoordinate**, const int32\_t **YCoordinate**, const n\_ACSIL::s\_GraphicsColor& **Color**);

#### Parameters

* **XCoordinate**:
* **YCoordinate**:
* **Color**:

#### Example

*No example provided by SierraChart*

### sc.FillEllipse()

[Link](#scfillellipse) - [Top](#top)

**Type**: Function

int32\_t **FillEllipse**(int **LeftRect**, int32\_t **TopRect**, int32\_t **RightRect**, int32\_t **BottomRect**, const n\_ACSIL::s\_GraphicsBrush& **Brush**);

#### Parameters

* **LeftRect**:
* **TopRect**:
* **RightRect**:
* **BottomRect**:
* **Brush**:

#### Example

*No example provided by SierraChart*

### sc.DrawEllipseOutline()

[Link](#scdrawellipseoutline) - [Top](#top)

**Type**: Function

int32\_t **DrawEllipseOutline**(int **LeftRect**, int32\_t **TopRect**, int32\_t **RightRect**, int32\_t **BottomRect**, const n\_ACSIL::s\_GraphicsBrush& **Brush**, int32\_t **Width**, int32\_t **Height**);

#### Parameters

* **LeftRect**:
* **TopRect**:
* **RightRect**:
* **BottomRect**:
* **Brush**:
* **Width**:
* **Height**:

#### Example

*No example provided by SierraChart*

### sc.DrawEllipseWithRadius()

[Link](#scdrawellipsewithradius) - [Top](#top)

**Type**: Function

int32\_t **DrawEllipseWithRadius**(int32\_t **StartPointX**, int32\_t **StartPointY**, int32\_t **EndPointX**, int32\_t **EndPointY**, int32\_t **SecondRadius**);

#### Parameters

* **StartPointX**:
* **StartPointY**:
* **EndPointX**:
* **EndPointY**:
* **SecondRadius**:

#### Example

*No example provided by SierraChart*

### sc.DrawEllipse()

[Link](#scdrawellipse) - [Top](#top)

**Type**: Function

int32\_t **DrawEllipse**(int32\_t **LeftRect**, int32\_t **TopRect**, int32\_t **RightRect**, int32\_t **BottomRect**);

#### Parameters

* **LeftRect**:
* **TopRect**:
* **RightRect**:
* **BottomRect**:

#### Example

*No example provided by SierraChart*

### sc.DrawArc()

[Link](#scdrawarc) - [Top](#top)

**Type**: Function

int32\_t **DrawArc**(int32\_t **LeftRect**, int32\_t **TopRect**, int32\_t **RightRect**, int32\_t **BottomRect**, int32\_t **StartArcX**, int32\_t **StartArcY**, int32\_t **EndArcX**, int32\_t **EndArcY**);

#### Parameters

* **LeftRect**:
* **TopRect**:
* **RightRect**:
* **BottomRect**:
* **StartArcX**:
* **StartArcY**:
* **EndArcX**:
* **EndArcY**:

#### Example

*No example provided by SierraChart*

### sc.DrawTextWithState()

[[Link](scdrawtextwithstate.html)] - [Top](#top)

**Type**: Function

int32\_t **DrawTextWithState**(const SCString& **Text**, const n\_ACSIL::s\_GraphicsPoint **TextAnchor**, const n\_ACSIL::s\_GraphicsSize **Size**, const uint32\_t **StateFlags**);

#### Parameters

* **Text**:
* **TextAnchor**:
* **Size**:
* **StateFlags**:

#### Example

*No example provided by SierraChart*

### sc.DrawTextInRectangle()

[[Link](scdrawtextinrectangle.html)] - [Top](#top)

**Type**: Function

int32\_t **DrawTextInRectangle**(const SCString& **Text**, const int32\_t **TextAnchorX**, const int32\_t **TextAnchorY**, const n\_ACSIL::s\_GraphicsRectangle& **Rectangle**, const uint32\_t **Options**);

#### Parameters

* **Text**:
* **TextAnchorX**:
* **TextAnchorY**:
* **Rectangle**:
* **Options**:

#### Example

*No example provided by SierraChart*

### sc.DrawTextAt()

[[Link](scdrawtextat.html)] - [Top](#top)

**Type**: Function

int32\_t **DrawTextAt**(const SCString& **Text**, const int32\_t **TextAnchorX**, const int32\_t **TextAnchorY**);

#### Parameters

* **Text**:
* **TextAnchorX**:
* **TextAnchorY**:

#### Example

*No example provided by SierraChart*

### sc.DrawText()

[[Link](scdrawtext.html)] - [Top](#top)

**Type**: Function

int32\_t **DrawText**(const SCString& **Text**, n\_ACSIL::s\_GraphicsRectangle& **r\_Rectangle**, const uint32\_t **Flags**);

#### Parameters

* **Text**:
* **r\_Rectangle**:
* **Flags**:

#### Example

*No example provided by SierraChart*

### sc.Internal\_DrawPolygon()

[[Link](scinternal_drawpolygon.html)] - [Top](#top)

**Type**: Function

int32\_t **Internal\_DrawPolygon**(const n\_ACSIL::s\_GraphicsPoint\* **p\_Points**, const int32\_t **NumPoints**);

#### Parameters

* **p\_Points**:
* **NumPoints**:

#### Example

*No example provided by SierraChart*

### sc.FillRectangleWithColor()

[[Link](scfillrectanglewithcolor.html)] - [Top](#top)

**Type**: Function

int32\_t **FillRectangleWithColor**( const n\_ACSIL::s\_GraphicsRectangle& **Rectangle**, const n\_ACSIL::s\_GraphicsColor& **Color**);

#### Parameters

* **Rectangle**:
* **Color**:

#### Example

*No example provided by SierraChart*

### sc.FillRectangle()

[[Link](scfillrectangle.html)] - [Top](#top)

**Type**: Function

int32\_t **FillRectangle**(const n\_ACSIL::s\_GraphicsRectangle& **Rectangle**, const n\_ACSIL::s\_GraphicsBrush& **Brush**);

#### Parameters

* **Rectangle**:
* **Brush**:

#### Example

*No example provided by SierraChart*

### sc.Draw3DRectangle()

[[Link](scdraw3drectangle.html)] - [Top](#top)

**Type**: Function

int32\_t **Draw3DRectangle**(const n\_ACSIL::s\_GraphicsRectangle& **Rectangle**, const n\_ACSIL::s\_GraphicsColor& **TopLeftColor**, const n\_ACSIL::s\_GraphicsColor& **BottomRightColor**);

#### Parameters

* **Rectangle**:
* **TopLeftColor**:
* **BottomRightColor**:

#### Example

*No example provided by SierraChart*

### sc.DrawFocusRectangle()

[[Link](scdrawfocusrectangle.html)] - [Top](#top)

**Type**: Function

int32\_t **DrawFocusRectangle**(const n\_ACSIL::s\_GraphicsRectangle& **Rectangle**);

#### Parameters

* **Rectangle**:

#### Example

*No example provided by SierraChart*

### sc.DrawRectangle()

[[Link](scdrawrectangle.html)] - [Top](#top)

**Type**: Function

int32\_t **DrawRectangle**(int32\_t **LeftRect**, int32\_t **TopRect**, int32\_t **RightRect**, int32\_t **BottomRect**);

#### Parameters

* **LeftRect**:
* **TopRect**:
* **RightRect**:
* **BottomRect**:

#### Example

*No example provided by SierraChart*

### sc.GetTextSizeWithFont()

[[Link](scgettextsizewithfont.html)] - [Top](#top)

**Type**: Function

int32\_t **GetTextSizeWithFont**(const SCString& **Text**, const n\_ACSIL::s\_GraphicsFont& **Font**, n\_ACSIL::s\_GraphicsSize& **r\_GraphicsSize**);

#### Parameters

* **Text**:
* **Font**:
* **r\_GraphicsSize**:

#### Example

*No example provided by SierraChart*

### sc.GetTextSize()

[[Link](scgettextsize.html)] - [Top](#top)

**Type**: Function

int32\_t **GetTextSize**(const SCString& **Text**, n\_ACSIL::s\_GraphicsSize& **r\_GraphicsSize**);

#### Parameters

* **Text**:
* **r\_GraphicsSize**:

#### Example

*No example provided by SierraChart*

### sc.GetTextHeightWithFont()

[[Link](scgettextheightwithfont.html)] - [Top](#top)

**Type**: Function

int32\_t **GetTextHeightWithFont**(const n\_ACSIL::s\_GraphicsFont& **Font**);

#### Parameters

* **Font**:

#### Example

*No example provided by SierraChart*

### sc.GetTextHeight()

[[Link](scgettextheight.html)] - [Top](#top)

**Type**: Function

int32\_t **GetTextHeight**();

#### Example

*No example provided by SierraChart*

### sc.CalculateFontPointSize()

[[Link](sccalculatefontpointsize.html)] - [Top](#top)

**Type**: Function

int32\_t **CalculateFontPointSize**(const int32\_t **LogicalHeight**);

#### Parameters

* **LogicalHeight**:

#### Example

*No example provided by SierraChart*

### sc.CalculateFontLogicalHeight()

[[Link](sccalculatefontlogicalheight.html)] - [Top](#top)

**Type**: Function

int32\_t **CalculateFontLogicalHeight**(const int32\_t **PointSize**);

#### Parameters

* **PointSize**:

#### Example

*No example provided by SierraChart*

### sc.GetDeviceCaps()

[[Link](scgetdevicecaps.html)] - [Top](#top)

**Type**: Function

int32\_t **GetDeviceCaps**( const int32\_t **Index**);

#### Parameters

* **Index**:

#### Example

*No example provided by SierraChart*

### sc.ResetTextFont()

[[Link](scresettextfont.html)] - [Top](#top)

**Type**: Function

int32\_t **ResetTextFont**();

#### Example

*No example provided by SierraChart*

### sc.ResetTextColor()

[[Link](scresettextcolor.html)] - [Top](#top)

**Type**: Function

int32\_t **ResetTextColor**();

#### Example

*No example provided by SierraChart*

### sc.ResetTextAlign()

[[Link](scresettextalign.html)] - [Top](#top)

**Type**: Function

int32\_t **ResetTextAlign**();

#### Example

*No example provided by SierraChart*

### sc.ResetPen()

[[Link](scresetpen.html)] - [Top](#top)

**Type**: Function

int32\_t **ResetPen**();

#### Example

*No example provided by SierraChart*

### sc.ResetBrush()

[[Link](scresetbrush.html)] - [Top](#top)

**Type**: Function

int32\_t **ResetBrush**();

#### Example

*No example provided by SierraChart*

### sc.ResetMixMode()

[[Link](scresetmixmode.html)] - [Top](#top)

**Type**: Function

int32\_t **ResetMixMode**();

#### Example

*No example provided by SierraChart*

### sc.ResetClippingRegion()

[[Link](scresetclippingregion.html)] - [Top](#top)

**Type**: Function

int32\_t **ResetClippingRegion**();

#### Example

*No example provided by SierraChart*

### sc.ResetBackgroundMode()

[[Link](scresetbackgroundmode.html)] - [Top](#top)

**Type**: Function

int32\_t **ResetBackgroundMode**();

#### Example

*No example provided by SierraChart*

### sc.ResetBackgroundColor()

[[Link](scresetbackgroundcolor.html)] - [Top](#top)

**Type**: Function

int32\_t **ResetBackgroundColor**();

#### Example

*No example provided by SierraChart*

### sc.SetTextFont()

[[Link](scsettextfont.html)] - [Top](#top)

**Type**: Function

int32\_t **SetTextFont**(const n\_ACSIL::s\_GraphicsFont& **TextFont**);

#### Parameters

* **TextFont**:

#### Example

*No example provided by SierraChart*

### sc.SetTextColor()

[[Link](scsettextcolor.html)] - [Top](#top)

**Type**: Function

int32\_t **SetTextColor**(const n\_ACSIL::s\_GraphicsColor& **TextColor**);

#### Parameters

* **TextColor**:

#### Example

*No example provided by SierraChart*

### sc.SetTextAlign()

[[Link](scsettextalign.html)] - [Top](#top)

**Type**: Function

int32\_t **SetTextAlign**(const uint32\_t **TextAlign**);

#### Parameters

* **TextAlign**:

#### Example

*No example provided by SierraChart*

### sc.SetPen()

[[Link](scsetpen.html)] - [Top](#top)

**Type**: Function

int32\_t **SetPen**(const n\_ACSIL::s\_GraphicsPen& **Pen**);

#### Parameters

* **Pen**:

#### Example

*No example provided by SierraChart*

### sc.SetBrush()

[[Link](scsetbrush.html)] - [Top](#top)

**Type**: Function

int32\_t **SetBrush**(const n\_ACSIL::s\_GraphicsBrush& **Brush**);

#### Parameters

* **Brush**:

#### Example

*No example provided by SierraChart*

### sc.SetMixMode()

[[Link](scsetmixmode.html)] - [Top](#top)

**Type**: Function

int32\_t **SetMixMode**(const int32\_t **Mode**);

#### Parameters

* **Mode**:

#### Example

*No example provided by SierraChart*

### sc.SetClippingRegionFromRectangle()

[[Link](scsetclippingregionfromrectangle.html)] - [Top](#top)

**Type**: Function

int32\_t **SetClippingRegionFromRectangle**(const n\_ACSIL::s\_GraphicsRectangle& **Rectangle**);

#### Parameters

* **Rectangle**:

#### Example

*No example provided by SierraChart*

### sc.SetBackgroundMode()

[[Link](scsetbackgroundmode.html)] - [Top](#top)

**Type**: Function

int32\_t **SetBackgroundMode**(const int32\_t **BackgroundMode**);

#### Parameters

* **BackgroundMode**:

#### Example

*No example provided by SierraChart*

### sc.SetBackgroundColor()

[[Link](scsetbackgroundcolor.html)] - [Top](#top)

**Type**: Function

int32\_t **SetBackgroundColor**(const n\_ACSIL::s\_GraphicsColor **BackgroundColor**);

#### Parameters

* **BackgroundColor**:

#### Example

*No example provided by SierraChart*

### sc.DrawPolygon()

[[Link](scdrawpolygon.html)] - [Top](#top)

**Type**: Function

int32\_t **DrawPolygon**(const n\_ACSIL::s\_GraphicsPoint& **Points**, int **t\_count**);

#### Parameters

* **Points**:
* **t\_Count**:

#### Example

*No example provided by SierraChart*

## Common Function Parameter Descriptions

[Link](#commonfunctionparameterdescriptions) - [Top](#top)

This is a list of all of the parameter descriptions for the common parameters for ACSIL graphics functions.

#### --

[[Link](#)] - [Top](#top)

int **--**: .

---

\*Last modified Monday, 10th February, 2025.
