# C1FileRogueForSchool

학교 과제를 위한 프로젝트입니다.

층의 모든 적을 처리해야 합니다.
플레이어는 6칸의 체력, 방어력, 공격력,  3칸의 포션 슬롯을 가집니다.
기본적으로 1의 공격력, 0의 방어력을 가집니다.

포션은 3가지 종류가 있고, 각각 H, S, V로 나타납니다.
- 회복의 포션은 체력을 전부 회복시켜 줍니다.
- 폭파의 포션은 주변 8칸의 적과 본인에게 피해를 2 줍니다.
- 강화의 포션은 방어력, 공격력 중 랜덤한 하나를 영구히 1 올립니다.

적은 등장한 층과 같은 체력을 지닙니다

맵은 10 x 10의 공간으로 만들어집니다. 생성 절차는 다음과 같습니다.
1. 맵의 제일 바깥쪽 한 칸을 벽으로 만듭니다.
2. 남은 8 x 8의 공간을 4 x 4로 나누어, 각 칸을 미리 생성된 프리셋 중 하나를 선택해서 채웁니다.
3. 가능한 한 위쪽 줄, 가능한 한 왼쪽 줄의 빈 공간을 플레이어의 시작 위치로 합니다.
4. 가능한 한 아래쪽 줄, 가능한 한 오른쪽 줄의 빈 공간을 플레이어의 도착 위치로 합니다.
5. 남은 공간을 30% 확률로 적, 30% 확률로 무작위 포션으로 채웁니다

게임이 시작하면, 플레이어는 시작 위치에 생성됩니다.
플레이어는 상 하 좌 우 중 벽이 없는 방향으로 이동하거나, 포션을 사용할 수 있습니다.
플레이어가 적의 위치로 이동하면, 적의 체력이 공격력만큼 줄어듭니다.
플레이어가 포션이 있는 위치로 이동하면, 포션을 인벤토리에 추가합니다.
플레이어가 도착 위치에 도착하면, 맵 전체에 적이 남아있는지 확인합니다. 적이 없다면 클리어 화면을 출력합니다.

맵은 다음의 형태로 출력됩니다.
- 빈 공간은 ' ' 로 출력됩니다
- 벽은 # 로 출력됩니다.
- 플레이어는 @ 로 출력됩니다.
- 적은 남은 체력에 따라 A, B, C로 출력됩니다.
- 포션은 H, S, V로 출력됩니다.

플레이어의 상태는 맵의 다음 줄에 출력합니다. 공격력, 방어력, 체력이 표시됩니다.
플레이어의 인벤토리는 상태의 다음 줄에 출력합니다.


