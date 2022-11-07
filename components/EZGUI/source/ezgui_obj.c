#include "ezgui_obj.h"
#include <stdlib.h>

/*
        ------------------------------------
        |                                  |
        |     --------------------         |
        |     |                  |         |
        |     | Children object  |         |
        |     |                  |         |
        |     --------------------         |
        |                                  |
        |           parrent object         |
        ------------------------------------

    child.coords là vị trí tương đối, tính theo parrent
*/

/**
 * @brief Thêm đối tượng con vào đối tượng cha
 * 
 * @param parrent 
 * @param children 
 * @return ezgui_obj_t* 
 */
void EZGUI_Object_Add(EZGUI_Objects_t *Parrent, EZGUI_Objects_t *Children) {
    uint8_t ChildrenCount = 0;
    if(Parrent->Children == 0) {
        Parrent->Children = (EZGUI_Objects_t **)malloc(sizeof(void (*)) << 1);
    }
    else {
        for(ChildrenCount = 0; Parrent->Children[ChildrenCount]; ChildrenCount++) {
        }
        Parrent->Children = (EZGUI_Objects_t **)realloc(Parrent->Children, sizeof(void (*)) * (ChildrenCount + 2));
    }
    if(Parrent->Children) {
        Parrent->Children[ChildrenCount] = Children;
        Parrent->Children[ChildrenCount + 1] = 0;
    }
}
EZGUI_Objects_t **EZGUI_Object_HasChildren(EZGUI_Objects_t *Parrent) {
    return Parrent->Children;
}
EZGUI_Objects_t *EZGUI_Object_Index(EZGUI_Objects_t *Parrent, uint8_t Index) {
    return Parrent->Children[Index];
}

// int8_t EZGUI_Object_Render(EZGUI_Objects_t *Parrent, Graphics_t *Graphic) {
//     uint8_t TempObjectData[100];
//     for(uint8_t IndexControl = 0; GUI->Object.Children[IndexControl] != 0; IndexControl++) {
//         memcpy((void *)TempObjectData, (void *)GUI->Object.Children[IndexControl], GUI->Object.Children[IndexControl]->InstanceSize);
//         ((EZGUI_Objects_t *)TempObjectData)->Point.X -= IndexHor;
//         ((EZGUI_Objects_t *)TempObjectData)->Point.Y -= IndexVer;
//         GUI->Object.Children[IndexControl]->Draw((EZGUI_Objects_t *)(TempObjectData), &DrawGraphic);
//     }
// }
