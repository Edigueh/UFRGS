ax1, ay1, ax2, ay2, bx1, by1, bx2, by2 = map(int, input().split())

area_a = (ax2 - ax1) * (ay2 - ay1)
area_b = (bx2 - bx1) * (by2 - by1)

overlap_x = max(0, min(ax2, bx2) - max(ax1, bx1))
overlap_y = max(0, min(ay2, by2) - max(ay1, by1))

area_intersecao = overlap_x * overlap_y

area_total = area_a + area_b - area_intersecao

print(area_total)
