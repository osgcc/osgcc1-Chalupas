VERSION 5.00
Begin VB.Form Form1 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Awesomest Program Evaar... The Sprite Editor"
   ClientHeight    =   9210
   ClientLeft      =   45
   ClientTop       =   360
   ClientWidth     =   13320
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   614
   ScaleMode       =   3  'Pixel
   ScaleWidth      =   888
   StartUpPosition =   3  'Windows Default
   Begin VB.ComboBox Combo1 
      Height          =   315
      ItemData        =   "Sprite Editor.frx":0000
      Left            =   8400
      List            =   "Sprite Editor.frx":0034
      Style           =   2  'Dropdown List
      TabIndex        =   17
      Top             =   600
      Width           =   4695
   End
   Begin VB.TextBox Text2 
      Height          =   285
      Left            =   120
      TabIndex        =   16
      Text            =   "sprite"
      Top             =   8400
      Width           =   3135
   End
   Begin VB.CommandButton Command6 
      Caption         =   "Clear"
      Height          =   255
      Left            =   5160
      TabIndex        =   15
      Top             =   8520
      Width           =   5775
   End
   Begin VB.CommandButton Command5 
      Caption         =   "Remove..."
      Height          =   255
      Left            =   5160
      TabIndex        =   14
      Top             =   8880
      Width           =   5775
   End
   Begin VB.ListBox lstCollRects 
      Height          =   1425
      Left            =   5160
      TabIndex        =   12
      Top             =   6960
      Width           =   5775
   End
   Begin VB.CommandButton Command4 
      Caption         =   "Save"
      Height          =   255
      Left            =   120
      TabIndex        =   11
      Top             =   8760
      Width           =   3135
   End
   Begin VB.CommandButton Command3 
      Caption         =   "New"
      Height          =   255
      Left            =   120
      TabIndex        =   10
      Top             =   120
      Width           =   3135
   End
   Begin VB.OptionButton optBotEdge 
      Caption         =   "Define Bottom Edge"
      Height          =   255
      Left            =   5880
      Style           =   1  'Graphical
      TabIndex        =   9
      Top             =   600
      Width           =   2415
   End
   Begin VB.OptionButton optCollRect 
      Caption         =   "Define Collision Rect"
      Height          =   255
      Left            =   3480
      Style           =   1  'Graphical
      TabIndex        =   8
      Top             =   600
      Value           =   -1  'True
      Width           =   2415
   End
   Begin VB.ListBox lstSpritePaths 
      Height          =   7275
      Left            =   1320
      TabIndex        =   7
      Top             =   1320
      Visible         =   0   'False
      Width           =   3135
   End
   Begin VB.PictureBox pctLoaded 
      Appearance      =   0  'Flat
      AutoRedraw      =   -1  'True
      AutoSize        =   -1  'True
      BackColor       =   &H80000005&
      BorderStyle     =   0  'None
      ForeColor       =   &H80000008&
      Height          =   2415
      Left            =   9600
      ScaleHeight     =   161
      ScaleMode       =   3  'Pixel
      ScaleWidth      =   233
      TabIndex        =   6
      Top             =   120
      Visible         =   0   'False
      Width           =   3495
   End
   Begin VB.PictureBox pctViewer 
      AutoRedraw      =   -1  'True
      Height          =   5535
      Left            =   3480
      ScaleHeight     =   365
      ScaleMode       =   3  'Pixel
      ScaleWidth      =   637
      TabIndex        =   5
      Top             =   960
      Width           =   9615
   End
   Begin VB.CommandButton Command2 
      Caption         =   "Remove"
      Height          =   255
      Left            =   120
      TabIndex        =   3
      Top             =   7920
      Width           =   3135
   End
   Begin VB.CommandButton Command1 
      Caption         =   "Add"
      Height          =   255
      Left            =   120
      TabIndex        =   2
      Top             =   600
      Width           =   3135
   End
   Begin VB.TextBox Text1 
      Height          =   285
      Left            =   120
      TabIndex        =   1
      Top             =   960
      Width           =   3135
   End
   Begin VB.ListBox lstSprites 
      Height          =   6495
      Left            =   120
      TabIndex        =   0
      Top             =   1320
      Width           =   3135
   End
   Begin VB.Label Label4 
      Caption         =   "The bottom edge defines how a sprite interacts with the level when falling."
      Height          =   255
      Left            =   3480
      TabIndex        =   19
      Top             =   360
      Width           =   6135
   End
   Begin VB.Label Label3 
      Caption         =   "Collision Rects define how a sprite interacts with the level."
      Height          =   255
      Left            =   3480
      TabIndex        =   18
      Top             =   0
      Width           =   6015
   End
   Begin VB.Label Label2 
      Caption         =   "Collision Detection Rectangles..."
      Height          =   255
      Left            =   5160
      TabIndex        =   13
      Top             =   6720
      Width           =   3495
   End
   Begin VB.Line Line2 
      X1              =   0
      X2              =   224
      Y1              =   552
      Y2              =   552
   End
   Begin VB.Line Line1 
      X1              =   224
      X2              =   224
      Y1              =   0
      Y2              =   616
   End
   Begin VB.Label Label1 
      Caption         =   "Add all sprites..."
      Height          =   255
      Left            =   120
      TabIndex        =   4
      Top             =   360
      Width           =   2415
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Declare Function BitBlt Lib "gdi32" (ByVal hDestDC As Long, ByVal x As Long, ByVal y As Long, ByVal nWidth As Long, ByVal nHeight As Long, ByVal hSrcDC As Long, ByVal xSrc As Long, ByVal ySrc As Long, ByVal dwRop As Long) As Long

Private Type RECT
        Left As Long
        Top As Long
        Right As Long
        Bottom As Long
End Type

Private Type SpriteInfo
    BottomX As Long
    BottomWidth As Long
    SpriteRect As RECT
    RectCount As Long
    CollisionRects() As RECT
End Type

Dim CurSprite As Integer

Dim CurRect As RECT

Dim SpriteArray() As SpriteInfo
Dim SpriteCount As Integer

Dim SpriteX As Long
Dim SpriteY As Long
Private Declare Function Rectangle Lib "gdi32" (ByVal hdc As Long, ByVal X1 As Long, ByVal Y1 As Long, ByVal X2 As Long, ByVal Y2 As Long) As Long




Private Sub Command1_Click()
Dim p As String

p = App.Path
If Right(p, 1) <> "\" Then
    p = p & "\"
End If

p = p & Text1.Text

If LCase(Dir(p)) = LCase(Text1.Text) Then
    lstSprites.AddItem "Frame " & lstSprites.ListCount & " - " & Text1.Text
    lstSpritePaths.AddItem p
    
    ReDim Preserve SpriteArray(0 To SpriteCount) As SpriteInfo
    SpriteArray(SpriteCount).RectCount = -1
    SpriteCount = SpriteCount + 1
Else
    MsgBox "Sprite image not found."
End If
End Sub

Private Sub Command3_Click()
lstSprites.Clear
lstSpritePaths.Clear

SpriteCount = 0
CurSprite = -1
End Sub

Private Sub Command4_Click()
' compile sprite sheet
Dim x As Long
Dim y As Long
Dim maxHeight As Long

Dim MaxiestHeight As Long
Dim MaxiestWidth As Long

maxHeight = 0

Dim p As String
p = App.Path

If (Right(p, 1) <> "\") Then
    p = p & "\"
End If

p = p & Text2.Text & ".spr"

If lstSprites.ListCount = -1 Then Exit Sub

If (LCase(Dir(p)) = LCase(Text2.Text & ".spr")) Then
    Kill p
End If

Open p For Binary Access Write As #1

Dim i As Long

Put 1, , CLng(Combo1.ListIndex)

Put 1, , CLng(lstSprites.ListCount)

pctViewer.Cls

For i = 0 To lstSprites.ListCount - 1
    pctLoaded.Picture = LoadPicture(lstSpritePaths.List(i))
    
    'place it on sprite sheet
    If x + pctLoaded.Width > pctViewer.Width Then
        If x > MaxiestWidth Then MaxiestWidth = x
        x = 0
        y = y + maxHeight
        maxHeight = 0
    End If
    
    If pctLoaded.Height > maxHeight Then
        maxHeight = pctLoaded.Height
    End If
    
    BitBlt pctViewer.hdc, x, y, pctLoaded.Width, pctLoaded.Height, pctLoaded.hdc, 0, 0, vbSrcCopy
    
    SpriteArray(i).SpriteRect.Left = x
    SpriteArray(i).SpriteRect.Right = pctLoaded.Width
    SpriteArray(i).SpriteRect.Top = y
    SpriteArray(i).SpriteRect.Bottom = pctLoaded.Height
    
    Put 1, , SpriteArray(i).BottomX
    Put 1, , SpriteArray(i).BottomWidth
    Put 1, , SpriteArray(i).SpriteRect
    Put 1, , SpriteArray(i).RectCount + 1
    
    Dim o As Long
    For o = 0 To SpriteArray(i).RectCount
        Put 1, , SpriteArray(i).CollisionRects(o)
    Next o
    
    x = x + pctLoaded.Width
Next i

If x > MaxiestWidth Then MaxiestWidth = x

y = y + maxHeight

pctLoaded.Width = MaxiestWidth
pctLoaded.Height = y

BitBlt pctLoaded.hdc, 0, 0, MaxiestWidth, y, pctViewer.hdc, 0, 0, vbSrcCopy

p = App.Path

If (Right(p, 1) <> "\") Then
    p = p & "\"
End If

p = p & Text2.Text & ".bmp"

Close #1

SavePicture pctLoaded.Image, p

pctViewer.Width = 641
pctViewer.Height = 369
End Sub

Private Sub Command5_Click()
If lstCollRects.ListIndex > -1 Then
    
    'rebuild list
    Dim i As Long
    
    For i = lstCollRects.ListIndex To SpriteArray(CurSprite).RectCount - 1
        SpriteArray(CurSprite).CollisionRects(i).Left = SpriteArray(CurSprite).CollisionRects(i + 1).Left
        SpriteArray(CurSprite).CollisionRects(i).Top = SpriteArray(CurSprite).CollisionRects(i + 1).Top
        SpriteArray(CurSprite).CollisionRects(i).Right = SpriteArray(CurSprite).CollisionRects(i + 1).Right
        SpriteArray(CurSprite).CollisionRects(i).Bottom = SpriteArray(CurSprite).CollisionRects(i + 1).Bottom
    Next i
    
    'remove this rect
    lstCollRects.RemoveItem lstCollRects.ListIndex
    
    'draw all rectangles
    BitBlt pctViewer.hdc, SpriteX, SpriteY, pctLoaded.Width, pctLoaded.Height, pctLoaded.hdc, 0, 0, vbSrcCopy
    
    SpriteArray(CurSprite).RectCount = SpriteArray(CurSprite).RectCount - 1
    For i = 0 To SpriteArray(CurSprite).RectCount
        Rectangle pctViewer.hdc, SpriteArray(CurSprite).CollisionRects(i).Left, SpriteArray(CurSprite).CollisionRects(i).Top, _
        SpriteArray(CurSprite).CollisionRects(i).Right, SpriteArray(CurSprite).CollisionRects(i).Bottom
    Next i
End If
End Sub

Private Sub Command6_Click()
lstCollRects.Clear

BitBlt pctViewer.hdc, SpriteX, SpriteY, pctLoaded.Width, pctLoaded.Height, pctLoaded.hdc, 0, 0, vbSrcCopy
End Sub

Private Sub Form_Load()
Command3_Click

Combo1.ListIndex = 0
End Sub

Private Sub lstSprites_Click()
pctLoaded.Picture = LoadPicture(lstSpritePaths.List(lstSprites.ListIndex))

SpriteX = (pctViewer.ScaleWidth - pctLoaded.Width) / 2
SpriteY = (pctViewer.ScaleHeight - pctLoaded.Height) / 2

pctViewer.Cls
BitBlt pctViewer.hdc, SpriteX, SpriteY, pctLoaded.Width, pctLoaded.Height, pctLoaded.hdc, 0, 0, vbSrcCopy

CurSprite = lstSprites.ListIndex

lstCollRects.Clear

Dim i As Long
For i = 0 To SpriteArray(CurSprite).RectCount
    lstCollRects.AddItem "{" & SpriteArray(CurSprite).CollisionRects(i).Left & ", " & _
                            SpriteArray(CurSprite).CollisionRects(i).Top & ", " & _
                            SpriteArray(CurSprite).CollisionRects(i).Right & ", " & _
                            SpriteArray(CurSprite).CollisionRects(i).Bottom & "}"
Next i

pctViewer.Refresh
End Sub

Private Sub pctViewer_MouseDown(Button As Integer, Shift As Integer, x As Single, y As Single)
If CurSprite = -1 Then Exit Sub

If optBotEdge.Value = True Then
    
    If (x < SpriteX) Then x = SpriteX
    If (x > SpriteX + pctLoaded.Width) Then x = SpriteX + pctLoaded.Width
    
    CurRect.Left = x
    CurRect.Top = SpriteY
Else
    If (x < SpriteX) Then x = SpriteX
    If (x > SpriteX + pctLoaded.Width) Then x = SpriteX + pctLoaded.Width
    If (y < SpriteY) Then y = SpriteY
    If (y > SpriteY + pctLoaded.Height) Then y = SpriteY + pctLoaded.Height
    
    CurRect.Left = x
    CurRect.Top = y
End If
End Sub

Private Sub pctViewer_MouseMove(Button As Integer, Shift As Integer, x As Single, y As Single)
If Button > 0 Then

    If optBotEdge.Value = True Then
        If CurSprite = -1 Then Exit Sub

        If (x < SpriteX) Then x = SpriteX
        If (x > SpriteX + pctLoaded.Width) Then x = SpriteX + pctLoaded.Width
        
        CurRect.Right = x
        CurRect.Bottom = SpriteY + pctLoaded.Height
        
        pctViewer.Cls
        
        BitBlt pctViewer.hdc, SpriteX, SpriteY, pctLoaded.Width, pctLoaded.Height, pctLoaded.hdc, 0, 0, vbSrcCopy
        Rectangle pctViewer.hdc, CurRect.Left, CurRect.Top, CurRect.Right, CurRect.Bottom
        
        pctViewer.Refresh
    Else
        If CurSprite = -1 Then Exit Sub

        If (x < SpriteX) Then x = SpriteX
        If (y < SpriteY) Then y = SpriteY
        If (x > SpriteX + pctLoaded.Width) Then x = SpriteX + pctLoaded.Width
        If (y > SpriteY + pctLoaded.Height) Then y = SpriteY + pctLoaded.Height
        
        CurRect.Right = x
        CurRect.Bottom = y
        
        pctViewer.Cls
        
        BitBlt pctViewer.hdc, SpriteX, SpriteY, pctLoaded.Width, pctLoaded.Height, pctLoaded.hdc, 0, 0, vbSrcCopy
        Rectangle pctViewer.hdc, CurRect.Left, CurRect.Top, CurRect.Right, CurRect.Bottom
        
        pctViewer.Refresh
    End If
    
End If
End Sub

Private Sub pctViewer_MouseUp(Button As Integer, Shift As Integer, x As Single, y As Single)
If (CurRect.Left <> CurRect.Right) And (CurRect.Top <> CurRect.Bottom) Then

'readjust rect
CurRect.Left = CurRect.Left - SpriteX
CurRect.Top = CurRect.Top - SpriteY
CurRect.Right = CurRect.Right - SpriteX
CurRect.Bottom = CurRect.Bottom - SpriteY

    If optBotEdge.Value = True Then
        
        'add bottom edge to array
        
        SpriteArray(CurSprite).BottomX = CurRect.Left
        SpriteArray(CurSprite).BottomWidth = CurRect.Right - CurRect.Left
    Else
        
        'add rectangle to array
        
        SpriteArray(CurSprite).RectCount = SpriteArray(CurSprite).RectCount + 1
        
        ReDim Preserve SpriteArray(CurSprite).CollisionRects(0 To SpriteArray(CurSprite).RectCount)
        
        SpriteArray(CurSprite).CollisionRects(SpriteArray(CurSprite).RectCount).Left = CurRect.Left
        SpriteArray(CurSprite).CollisionRects(SpriteArray(CurSprite).RectCount).Bottom = CurRect.Bottom
        SpriteArray(CurSprite).CollisionRects(SpriteArray(CurSprite).RectCount).Top = CurRect.Top
        SpriteArray(CurSprite).CollisionRects(SpriteArray(CurSprite).RectCount).Right = CurRect.Right
        
        'add the rectangle to the list
        
        lstCollRects.AddItem "{" & CurRect.Left & ", " & CurRect.Top & ", " & CurRect.Right & ", " & CurRect.Bottom & "}"
        
        'draw all rectangles
        
        BitBlt pctViewer.hdc, SpriteX, SpriteY, pctLoaded.Width, pctLoaded.Height, pctLoaded.hdc, 0, 0, vbSrcCopy
        
        Dim i As Long
        For i = 0 To SpriteArray(CurSprite).RectCount
            Rectangle pctViewer.hdc, SpriteArray(CurSprite).CollisionRects(i).Left, SpriteArray(CurSprite).CollisionRects(i).Top, _
            SpriteArray(CurSprite).CollisionRects(i).Right, SpriteArray(CurSprite).CollisionRects(i).Bottom
        Next i
        
        pctViewer.Refresh
    End If
End If
End Sub
