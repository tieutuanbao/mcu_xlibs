#include "ezgui_image.h"
#include <stdlib.h>

void Image_Draw(DrawPoint_t DrawPoint_Drv, EZGUI_Image_t *Image, Graphics_t *Graphic, Point_t Offset) {
    Point_t DrawPos = {Image->Object.Point.X + Offset.X, Image->Object.Point.Y + Offset.Y};
    Area_t ImageAreaCanDraw;
    /* Ảnh nằm ngoài Graphic */
    if(DrawPos.X > Graphic->Size.Width) return;     // Ảnh nằm ngoài bên phải Graphic
    if(DrawPos.Y > Graphic->Size.Height) return;    // Ảnh nằm ngoài bên dưới Graphic
    if((DrawPos.X + Image->Object.Size.Width) < 0) return;      // Ảnh nằm ngoài bên trái Graphic
    if((DrawPos.Y + Image->Object.Size.Height) < 0) return;     // Ảnh nằm ngoài bên phải Graphic

    if(DrawPos.X >= 0) ImageAreaCanDraw.Start.X = 0;
    else ImageAreaCanDraw.Start.X = -DrawPos.X;
    if(DrawPos.Y >= 0) ImageAreaCanDraw.Start.Y = 0;
    else ImageAreaCanDraw.Start.Y = -DrawPos.Y;

    ImageAreaCanDraw.Stop.X = (int32_t)Graphic->Size.Width - DrawPos.X - 1;
    if(ImageAreaCanDraw.Stop.X > Image->Object.Size.Width) ImageAreaCanDraw.Stop.X = Image->Object.Size.Width;
    ImageAreaCanDraw.Stop.Y = (int32_t)Graphic->Size.Height - DrawPos.Y - 1;
    if(ImageAreaCanDraw.Stop.Y > Image->Object.Size.Height) ImageAreaCanDraw.Stop.Y = Image->Object.Size.Height;

    Color_ARGB_t *Buf = (Color_ARGB_t *)malloc(((ImageAreaCanDraw.Stop.X - ImageAreaCanDraw.Start.X) + 1) * ((ImageAreaCanDraw.Stop.Y - ImageAreaCanDraw.Start.Y) + 1) * 4);
    Image->GetData_Driver(Image->FilePath, Buf, ImageAreaCanDraw);
    EZGUI_Draw_Image(DrawPoint_Drv, Graphic, DrawPos, Image->Object.Size, Buf);
    free(Buf);
}


EZGUI_Image_t *EZGUI_Image_new(EZGUI_Objects_t *Parrent) {
    EZGUI_Image_t *Image = (EZGUI_Image_t *)malloc(sizeof(EZGUI_Image_t));
    if(Image) {
        Image->Object.InstanceSize = sizeof(EZGUI_Image_t);
        Image->Object.Draw = (Draw_t)Image_Draw;
        Image->Object.Point = (Point_t){0, 0};
        Image->GetSize_Driver = 0;
        Image->GetData_Driver = 0;
        Image->Object.Size = (Size_t){10, 10};
        EZGUI_Object_Add(Parrent, (EZGUI_Objects_t *)Image);
    }
    return Image;
}
