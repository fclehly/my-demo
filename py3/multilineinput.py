#coding=utf-8
# 本题为考试多行输入输出规范示例，无需提交，不计分。
import sys
if __name__ == "__main__":
    # 读取第一行的n
    # n = int(sys.stdin.readline().strip())
    # line2 = sys.stdin.readline().strip()
    # nums = [int(item) for item in line2.split()]
    nums = [1, 2,2,2,22,22, 44,55]
    nums.sort()
    l, r = 0, len(nums) - 1
    ans = 0
    while l < r:
        if nums[l] + nums[r] == 24:
            count_l = 1
            count_r = 1
            while l < r and nums[l] == nums[l + 1]:
                l += 1
                count_l += 1
            while l < r and nums[r] == nums[r - 1]:
                r -= 1
                count_r += 1
            ans += count_l * count_r
            l += 1
            r -= 1
        elif nums[l] + nums[r] > 24:
            r -= 1
        else:
            l += 1
    print(ans)