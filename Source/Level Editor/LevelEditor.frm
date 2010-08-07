VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "Super Sweet Level Editor"
   ClientHeight    =   10155
   ClientLeft      =   60
   ClientTop       =   375
   ClientWidth     =   19080
   LinkTopic       =   "Form1"
   ScaleHeight     =   677
   ScaleMode       =   3  'Pixel
   ScaleWidth      =   1272
   StartUpPosition =   3  'Windows Default
   Begin VB.PictureBox pctDeath 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BorderStyle     =   0  'None
      ForeColor       =   &H80000008&
      Height          =   480
      Left            =   7680
      Picture         =   "LevelEditor.frx":0000
      ScaleHeight     =   32
      ScaleMode       =   3  'Pixel
      ScaleWidth      =   32
      TabIndex        =   34
      Top             =   720
      Width           =   480
   End
   Begin VB.OptionButton optVert 
      Caption         =   "Scroll BG Vert"
      Height          =   375
      Left            =   14520
      TabIndex        =   33
      Top             =   240
      Value           =   -1  'True
      Width           =   2655
   End
   Begin VB.OptionButton optHoriz 
      Caption         =   "Scroll BG Horiz"
      Height          =   375
      Left            =   14520
      TabIndex        =   32
      Top             =   600
      Width           =   2655
   End
   Begin VB.TextBox Text6 
      Height          =   285
      Left            =   12480
      TabIndex        =   31
      Text            =   "tilemap1.bmp"
      Top             =   840
      Width           =   1935
   End
   Begin VB.TextBox Text5 
      Height          =   285
      Left            =   12480
      TabIndex        =   30
      Text            =   "bg2.bmp"
      Top             =   480
      Width           =   1935
   End
   Begin VB.TextBox Text4 
      Height          =   285
      Left            =   12480
      TabIndex        =   29
      Text            =   "Level Title"
      Top             =   120
      Width           =   1935
   End
   Begin VB.PictureBox pctMask 
      Appearance      =   0  'Flat
      AutoRedraw      =   -1  'True
      BackColor       =   &H80000005&
      BorderStyle     =   0  'None
      ForeColor       =   &H80000008&
      Height          =   480
      Left            =   0
      Picture         =   "LevelEditor.frx":0C42
      ScaleHeight     =   32
      ScaleMode       =   3  'Pixel
      ScaleWidth      =   32
      TabIndex        =   28
      Top             =   0
      Visible         =   0   'False
      Width           =   480
   End
   Begin VB.PictureBox pctPassable 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BorderStyle     =   0  'None
      ForeColor       =   &H80000008&
      Height          =   480
      Left            =   5640
      Picture         =   "LevelEditor.frx":1884
      ScaleHeight     =   32
      ScaleMode       =   3  'Pixel
      ScaleWidth      =   32
      TabIndex        =   23
      Top             =   120
      Width           =   480
   End
   Begin VB.PictureBox pctForeground 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BorderStyle     =   0  'None
      ForeColor       =   &H80000008&
      Height          =   480
      Left            =   5640
      Picture         =   "LevelEditor.frx":24C6
      ScaleHeight     =   32
      ScaleMode       =   3  'Pixel
      ScaleWidth      =   32
      TabIndex        =   22
      Top             =   720
      Width           =   480
   End
   Begin VB.PictureBox pctBackground 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BorderStyle     =   0  'None
      ForeColor       =   &H80000008&
      Height          =   480
      Left            =   5040
      Picture         =   "LevelEditor.frx":3108
      ScaleHeight     =   32
      ScaleMode       =   3  'Pixel
      ScaleWidth      =   32
      TabIndex        =   21
      Top             =   720
      Width           =   480
   End
   Begin VB.PictureBox pctSolid 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BorderStyle     =   0  'None
      ForeColor       =   &H80000008&
      Height          =   480
      Left            =   5040
      Picture         =   "LevelEditor.frx":3D4A
      ScaleHeight     =   32
      ScaleMode       =   3  'Pixel
      ScaleWidth      =   32
      TabIndex        =   20
      Top             =   120
      Width           =   480
   End
   Begin VB.TextBox Text3 
      Height          =   285
      Left            =   10920
      TabIndex        =   19
      Text            =   "level.lvl"
      Top             =   720
      Width           =   1335
   End
   Begin VB.CommandButton Command3 
      Caption         =   "Load"
      Height          =   255
      Left            =   10920
      TabIndex        =   18
      Top             =   480
      Width           =   1335
   End
   Begin VB.CommandButton Command2 
      Caption         =   "Save"
      Height          =   255
      Left            =   10920
      TabIndex        =   17
      Top             =   240
      Width           =   1335
   End
   Begin VB.CommandButton Command1 
      Caption         =   "Init"
      Height          =   255
      Left            =   8640
      TabIndex        =   16
      Top             =   720
      Width           =   1695
   End
   Begin VB.TextBox Text2 
      Height          =   285
      Left            =   9720
      TabIndex        =   14
      Text            =   "0"
      Top             =   360
      Width           =   615
   End
   Begin VB.TextBox Text1 
      Height          =   285
      Left            =   8640
      TabIndex        =   13
      Text            =   "0"
      Top             =   360
      Width           =   615
   End
   Begin VB.PictureBox pctCurTile 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   480
      Left            =   2640
      ScaleHeight     =   30
      ScaleMode       =   3  'Pixel
      ScaleWidth      =   30
      TabIndex        =   10
      Top             =   480
      Width           =   480
   End
   Begin VB.PictureBox pctTileMap 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   8670
      Left            =   0
      ScaleHeight     =   576
      ScaleMode       =   3  'Pixel
      ScaleWidth      =   576
      TabIndex        =   9
      Top             =   1320
      Width           =   8670
   End
   Begin VB.PictureBox pctLevel 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   7200
      Left            =   9000
      ScaleHeight     =   478
      ScaleMode       =   3  'Pixel
      ScaleWidth      =   638
      TabIndex        =   0
      Top             =   2040
      Width           =   9600
   End
   Begin VB.Label Label16 
      Height          =   255
      Left            =   14400
      TabIndex        =   35
      Top             =   1320
      Width           =   2535
   End
   Begin VB.Label Label15 
      Alignment       =   1  'Right Justify
      Caption         =   "Background"
      Height          =   255
      Left            =   3480
      TabIndex        =   27
      Top             =   840
      Width           =   1455
   End
   Begin VB.Label Label14 
      Alignment       =   1  'Right Justify
      Caption         =   "Solid"
      Height          =   255
      Left            =   3480
      TabIndex        =   26
      Top             =   240
      Width           =   1455
   End
   Begin VB.Label Label13 
      Caption         =   "Foreground"
      Height          =   255
      Left            =   6240
      TabIndex        =   25
      Top             =   840
      Width           =   1455
   End
   Begin VB.Label Label12 
      Caption         =   "Passable"
      Height          =   255
      Left            =   6240
      TabIndex        =   24
      Top             =   240
      Width           =   1455
   End
   Begin VB.Label Label11 
      Alignment       =   2  'Center
      Caption         =   "by"
      Height          =   255
      Left            =   9240
      TabIndex        =   15
      Top             =   360
      Width           =   495
   End
   Begin VB.Label Label10 
      Caption         =   "Create Level"
      Height          =   255
      Left            =   8280
      TabIndex        =   12
      Top             =   120
      Width           =   2535
   End
   Begin VB.Label Label9 
      Alignment       =   1  'Right Justify
      Caption         =   "Current Tile:"
      Height          =   255
      Left            =   720
      TabIndex        =   11
      Top             =   600
      Width           =   1815
   End
   Begin VB.Label Label8 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BorderStyle     =   1  'Fixed Single
      ForeColor       =   &H80000008&
      Height          =   255
      Left            =   9000
      TabIndex        =   8
      Top             =   9345
      Width           =   9600
   End
   Begin VB.Label Label7 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BorderStyle     =   1  'Fixed Single
      ForeColor       =   &H80000008&
      Height          =   255
      Left            =   9000
      TabIndex        =   7
      Top             =   1680
      Width           =   9600
   End
   Begin VB.Label Label6 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BorderStyle     =   1  'Fixed Single
      ForeColor       =   &H80000008&
      Height          =   7200
      Left            =   18705
      TabIndex        =   6
      Top             =   2040
      Width           =   255
   End
   Begin VB.Label Label5 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BorderStyle     =   1  'Fixed Single
      ForeColor       =   &H80000008&
      Height          =   7200
      Left            =   8640
      TabIndex        =   5
      Top             =   2040
      Width           =   255
   End
   Begin VB.Label Label4 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BorderStyle     =   1  'Fixed Single
      ForeColor       =   &H80000008&
      Height          =   7200
      Left            =   18585
      TabIndex        =   4
      Top             =   2040
      Width           =   135
   End
   Begin VB.Label Label3 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BorderStyle     =   1  'Fixed Single
      ForeColor       =   &H80000008&
      Height          =   7200
      Left            =   8880
      TabIndex        =   3
      Top             =   2040
      Width           =   135
   End
   Begin VB.Label Label2 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BorderStyle     =   1  'Fixed Single
      ForeColor       =   &H80000008&
      Height          =   135
      Left            =   9000
      TabIndex        =   2
      Top             =   9225
      Width           =   9600
   End
   Begin VB.Label Label1 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BorderStyle     =   1  'Fixed Single
      ForeColor       =   &H80000008&
      Height          =   135
      Left            =   9000
      TabIndex        =   1
      Top             =   1920
      Width           =   9600
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Dim LevelMatrix() As Long
Dim LevelTypes() As Long

Dim LevelX As Long
Dim LevelY As Long

Dim LevelWidth As Integer
Dim LevelHeight As Integer

Dim CurTileID As Long

Dim FloodTileID As Long

Private Declare Function BitBlt Lib "gdi32" (ByVal hDestDC As Long, ByVal x As Long, ByVal y As Long, ByVal nWidth As Long, ByVal nHeight As Long, ByVal hSrcDC As Long, ByVal xSrc As Long, ByVal ySrc As Long, ByVal dwRop As Long) As Long

Private Type spriteInfo
    id As Long
    tx As Long
    ty As Long
End Type

Dim sprites(0 To 256) As spriteInfo
Private spritesCount

Private Sub Command1_Click()
LevelWidth = Int(Text1)
LevelHeight = Int(Text2)

ReDim LevelMatrix(0 To LevelWidth - 1, 0 To LevelHeight - 1) As Long
ReDim LevelTypes(0 To LevelWidth - 1, 0 To LevelHeight - 1) As Long

LevelY = LevelHeight - 15
LevelX = 0
End Sub

Private Sub Command2_Click()
Dim p As String
p = App.Path

If Right(p, 1) <> "\" Then
    p = p & "\"
End If

p = p & Text3.Text

If LCase(Dir(p)) = LCase(Text3.Text) Then
    Kill p
End If

Open p For Binary Access Write As #1
    Put 1, , LevelWidth
    Put 1, , LevelHeight
    Put 1, , LevelMatrix
    Put 1, , LevelTypes
    If optVert.Value = True Then
        Put 1, , CInt(1)
    Else
        Put 1, , CInt(0)
    End If
    
    Put 1, , CByte(Len(Text4.Text))
    Put 1, , Text4.Text
    Put 1, , CByte(Len(Text5.Text))
    Put 1, , Text5.Text
    Put 1, , CByte(Len(Text6.Text))
    Put 1, , Text6.Text
    
    Put 1, , CLng(spritesCount)
    
    Put 1, , sprites
Close #1

End Sub

Private Sub Command3_Click()

Dim p As String
p = App.Path

If Right(p, 1) <> "\" Then
    p = p & "\"
End If

p = p & Text3.Text

Dim strlen As Byte
Dim bytes() As Byte

Dim i As Integer

If (Dir(p, vbNormal) = "") Then
    MsgBox "File not found."
    Exit Sub
End If

Open p For Binary Access Read As #2
    Get 2, , LevelWidth
    Get 2, , LevelHeight
    
    ReDim LevelMatrix(0 To LevelWidth - 1, 0 To LevelHeight - 1) As Long
    ReDim LevelTypes(0 To LevelWidth - 1, 0 To LevelHeight - 1) As Long
    
    Get 2, , LevelMatrix
    Get 2, , LevelTypes
    
    Get 2, , i
    
    If i = 1 Then
        optVert.Value = True
    Else
        optHoriz.Value = True
    End If
    
    Get 2, , strlen
    ReDim bytes(0 To strlen - 1) As Byte
    Get 2, , bytes
    
    Text4.Text = StrConv(bytes, vbUnicode)
    
    Get 2, , strlen
    ReDim bytes(0 To strlen - 1) As Byte
    Get 2, , bytes
    
    Text5.Text = StrConv(bytes, vbUnicode)
    
    Get 2, , strlen
    ReDim bytes(0 To strlen - 1) As Byte
    Get 2, , bytes
    
    Text6.Text = StrConv(bytes, vbUnicode)
    
    
Close #2

p = App.Path
If Right(p, 1) <> "\" Then
    p = p & "\"
End If

p = p & Text6.Text

pctTileMap.Picture = LoadPicture(p)

LevelY = LevelHeight - 15
LevelX = 0

DrawLevel
End Sub

Private Sub Form_Load()
LevelWidth = -1
LevelHeight = -1

LevelX = 0
LevelY = 0

Dim p As String
p = App.Path
If Right(p, 1) <> "\" Then
    p = p & "\"
End If

p = p & "tileMap1.bmp"

pctTileMap.Picture = LoadPicture(p)
End Sub

Sub DrawLevel()
Dim x As Long
Dim y As Long

Dim tx As Long
Dim ty As Long

For y = 0 To 14
    If LevelY + y >= LevelHeight Then
        Exit For
    End If
For x = 0 To 19

    If LevelX + x >= LevelWidth Then
        Exit For
    End If

    tx = LevelMatrix(x + LevelX, y + LevelY)
    ty = Fix(tx / 18)
    tx = tx Mod 18

    BitBlt pctLevel.hdc, x * 32, y * 32, 32, 32, pctTileMap.hdc, tx * 32, ty * 32, vbSrcCopy

    tx = LevelTypes(x + LevelX, y + LevelY)
    
    Dim hdc As Long
    
    Select Case tx
        Case 0
            hdc = pctBackground.hdc
        Case 1
            hdc = pctForeground.hdc
        Case 2
            hdc = pctPassable.hdc
        Case 3
            hdc = pctSolid.hdc
        Case 4
            hdc = pctDeath.hdc
    End Select
    
    BitBlt pctLevel.hdc, x * 32, y * 32, 32, 32, hdc, 0, 0, vbSrcAnd
    BitBlt pctLevel.hdc, x * 32, y * 32, 32, 32, pctMask.hdc, 0, 0, vbSrcPaint
Next x
Next y
End Sub

Private Sub Label1_Click()
LevelY = LevelY - 1
If LevelY < 0 Then LevelY = 0

DrawLevel
End Sub

Private Sub Label2_Click()
LevelY = LevelY + 1
If LevelY >= (LevelHeight - 15) Then LevelY = LevelHeight - 15

DrawLevel
End Sub

Private Sub Label3_Click()
LevelX = LevelX - 1
If LevelX < 0 Then LevelX = 0

DrawLevel
End Sub

Private Sub Label4_Click()

LevelX = LevelX + 1
If LevelX >= (LevelWidth - 20) Then LevelX = LevelWidth - 20

DrawLevel
End Sub

Private Sub Label5_Click()

LevelX = LevelX - 20
If LevelX < 0 Then LevelX = 0

DrawLevel
End Sub

Private Sub Label6_Click()


LevelX = LevelX + 20
If LevelX >= (LevelWidth - 20) Then LevelX = LevelWidth - 20

DrawLevel
End Sub

Private Sub Label7_Click()
LevelY = LevelY - 15
If LevelY < 0 Then LevelY = 0

DrawLevel
End Sub

Private Sub Label8_Click()

LevelY = LevelY + 15
If LevelY >= (LevelHeight - 15) Then LevelY = LevelHeight - 15

DrawLevel
End Sub

Private Sub pctBackground_Click()

CurTileID = -1
BitBlt pctCurTile.hdc, 0, 0, 32, 32, pctBackground.hdc, 0, 0, vbSrcCopy
End Sub

Private Sub pctDeath_Click()
CurTileID = -5
BitBlt pctCurTile.hdc, 0, 0, 32, 32, pctDeath.hdc, 0, 0, vbSrcCopy
End Sub

Private Sub pctForeground_Click()
CurTileID = -2
BitBlt pctCurTile.hdc, 0, 0, 32, 32, pctForeground.hdc, 0, 0, vbSrcCopy
End Sub

Sub FloodFill(x As Long, y As Long)
If x >= LevelWidth Then Exit Sub

If y >= LevelHeight Then Exit Sub

If x < 0 Then Exit Sub

If y < 0 Then Exit Sub

If (CurTileID < 0) Then
    If LevelTypes(x, y) = FloodTileID Then
        LevelTypes(x, y) = Abs(CurTileID) - 1
    Else
        Exit Sub
    End If
Else
    If LevelMatrix(x, y) = FloodTileID Then
        LevelMatrix(x, y) = CurTileID
    Else
        Exit Sub
    End If
End If

FloodFill x + 1, y
FloodFill x - 1, y
FloodFill x, y + 1
FloodFill x, y - 1
End Sub

Private Sub pctLevel_MouseDown(Button As Integer, Shift As Integer, x As Single, y As Single)

Dim tx As Long
Dim ty As Long

tx = Fix(x / 32)
ty = Fix(y / 32)

If LevelX + tx >= LevelWidth Then Exit Sub

If LevelY + ty >= LevelHeight Then Exit Sub

If Button = vbRightButton Then
    
    If (CurTileID < 0) Then
        FloodTileID = LevelTypes(LevelX + tx, LevelY + ty)
        If FloodTileID = Abs(CurTileID) - 1 Then Exit Sub
    Else
        FloodTileID = LevelMatrix(LevelX + tx, LevelY + ty)
        If FloodTileID = CurTileID Then Exit Sub
    End If
    
    
    FloodFill LevelX + tx, LevelY + ty
    
    DrawLevel
    Exit Sub
End If

If (CurTileID < 0) Then
    LevelTypes(LevelX + tx, LevelY + ty) = Abs(CurTileID) - 1
Else
    LevelMatrix(LevelX + tx, LevelY + ty) = CurTileID
End If

DrawLevel
End Sub

Private Sub pctLevel_MouseMove(Button As Integer, Shift As Integer, x As Single, y As Single)

    Dim tx As Long
    Dim ty As Long
    
    If Shift = vbShiftMask Then
    
    tx = Fix(x / 32)
    ty = Fix(y / 32)
    
    If LevelX + tx >= LevelWidth Then Exit Sub
    
    If LevelY + ty >= LevelHeight Then Exit Sub
    
    If (CurTileID < 0) Then
        LevelTypes(LevelX + tx, LevelY + ty) = Abs(CurTileID) - 1
    Else
        LevelMatrix(LevelX + tx, LevelY + ty) = CurTileID
    End If
    
    DrawLevel
Else
    
    tx = Fix(x / 32)
    ty = Fix(y / 32)
    
    If LevelX + tx >= LevelWidth Then Exit Sub
    
    If LevelY + ty >= LevelHeight Then Exit Sub
    
    Label16 = LevelX + tx & ", " & LevelY + ty
End If
End Sub

Private Sub pctLevel_Paint()
DrawLevel
End Sub

Private Sub pctPassable_Click()
CurTileID = -3
BitBlt pctCurTile.hdc, 0, 0, 32, 32, pctPassable.hdc, 0, 0, vbSrcCopy
End Sub

Private Sub pctSolid_Click()
CurTileID = -4
BitBlt pctCurTile.hdc, 0, 0, 32, 32, pctSolid.hdc, 0, 0, vbSrcCopy
End Sub

Private Sub pctTileMap_MouseDown(Button As Integer, Shift As Integer, x As Single, y As Single)
Dim tx As Long
Dim ty As Long

tx = Fix(x / 32)
ty = Fix(y / 32)

BitBlt pctCurTile.hdc, 0, 0, 32, 32, pctTileMap.hdc, (tx * 32), (ty * 32), vbSrcCopy

CurTileID = (ty * 18) + tx
End Sub
