Yêu cầu thiết kế:
- Thư viện lập trình GUI cho những dòng VĐK dung lượng Ram thấp.
- Gọn, nhẹ, dễ sử dụng.
- Hoạt động theo Non-Blocking Code.
Ý tưởng:
- Chia màn hình thành các Graphics nhỏ hơn có kích thước tùy biến.
- Mỗi Graphic nhỏ có thể vẽ lên các Widgets/Controls/Objects theo tọa độ bất kỳ.
- Mỗi Graphic nhỏ có thể gán một Driver vẽ điểm ảnh riêng.

- Sử dụng chung 1 Buffer Graphic
Cấu trúc của GUI:
- Danh sách các Đối tượng Render
    + Phương thức Render:
        - Đối tượng Render
        - Phương thức Render
        - Kích thước Render
- Render:
    + *Buffer[2]: Nếu dùng DMA thì 1 Buffer dùng để in ra màn hình trong khi Buffer còn lại đang Render.
    + BufferSize
- Monitor:
    + *List:
        - Kích thước tổng của Monitor.
        - Driver FrameBuffer
        - Driver DrawPoint
    + MCount: Đếm số lượng màn hình.
