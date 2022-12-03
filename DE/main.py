from tqdm import trange
import numpy as np

# ---- Setting ----
DEV = False
T = 1
Rt = 0.95
Iter = 200
Round = 100
N = 4 if DEV else 101
TestCase = "../test.txt" if DEV else "../input.txt"
Threshold = 720

# ---- Variable ----
wij = np.zeros((N+1, N+1))


def mapping(n):
    return 2*n-1


def fit_fun(result):
    # calc E
    size = len(result)
    sum = 0
    for i in range(1, size):
        for j in range(i+1, size):
            sum += wij[i, j]*mapping(result[i])*mapping(result[j])
    return sum


# ---- Class ----
class Unit:
    # 初始化
    def __init__(self, x_min, x_max, dim):
        self.__pos = np.array(
            [x_min + np.random.randint(0, 2) for i in range(dim)])
        self.__mutation = np.array([0.0 for i in range(dim)])  # 个体突变后的向量
        self.__crossover = np.array([0.0 for i in range(dim)])  # 个体交叉后的向量
        self.__fitnessValue = fit_fun(self.__pos)  # 个体适应度

    def set_pos(self, i, value):
        self.__pos[i] = value

    def get_pos(self):
        return self.__pos

    def set_mutation(self, i, value):
        self.__mutation[i] = value

    def get_mutation(self):
        return self.__mutation

    def set_crossover(self, i, value):
        self.__crossover[i] = value

    def get_crossover(self):
        return self.__crossover

    def set_fitness_value(self, value):
        self.__fitnessValue = value

    def get_fitness_value(self):
        return self.__fitnessValue


class DE:
    def __init__(self, dim, size, iter_num, x_min, x_max, best_fitness_value=0, F=0.5, CR=0.8):
        self.F = F
        self.CR = CR
        self.dim = dim  # 维度
        self.size = size  # 总群个数
        self.iter_num = iter_num  # 迭代次数
        self.x_min = x_min
        self.x_max = x_max
        self.best_fitness_value = best_fitness_value
        self.best_position = [0.0 for i in range(dim)]  # 全局最优解
        self.fitness_val_list = []  # 每次迭代最优适应值
        # 对种群进行初始化
        self.unit_list = [Unit(self.x_min, self.x_max, self.dim)
                          for i in range(self.size)]
        print("INIT")

    def get_kth_unit(self, k):
        return self.unit_list[k]

    def set_bestFitnessValue(self, value):
        self.best_fitness_value = value

    def get_bestFitnessValue(self):
        return self.best_fitness_value

    def set_bestPosition(self, i, value):
        self.best_position[i] = value

    def get_bestPosition(self):
        return self.best_position

    # 变异
    def mutation_fun(self):
        for i in range(self.size):
            r1 = r2 = r3 = 0
            while r1 == i or r2 == i or r3 == i or r2 == r1 or r3 == r1 or r3 == r2:
                r1 = np.random.randint(0, self.size - 1)  # 随机数范围为[0,size-1]的整数
                r2 = np.random.randint(0, self.size - 1)
                r3 = np.random.randint(0, self.size - 1)
            mutation = self.get_kth_unit(r1).get_pos() + \
                self.F * (self.get_kth_unit(r2).get_pos() -
                          self.get_kth_unit(r3).get_pos())
            for j in range(self.dim):
                self.get_kth_unit(i).set_mutation(
                    j, 0 if mutation[j] < 0.5 else 1)

    # 交叉
    def crossover(self):
        for unit in self.unit_list:
            for j in range(self.dim):
                rand_j = np.random.randint(0, self.dim - 1)
                rand_float = np.random.random()
                if rand_float <= self.CR or rand_j == j:
                    unit.set_crossover(j, unit.get_mutation()[j])
                else:
                    unit.set_crossover(j, unit.get_pos()[j])

    # 选择
    def selection(self):
        for unit in self.unit_list:
            new_fitness_value = fit_fun(unit.get_crossover())
            if new_fitness_value > unit.get_fitness_value():
                unit.set_fitness_value(new_fitness_value)
                for i in range(self.dim):
                    unit.set_pos(i, unit.get_crossover()[i])
            if new_fitness_value > self.get_bestFitnessValue():
                self.set_bestFitnessValue(new_fitness_value)
                for j in range(self.dim):
                    self.set_bestPosition(j, unit.get_crossover()[j])

    def update(self):
        t = trange(self.iter_num, ascii=True)
        for i in t:
            self.mutation_fun()
            self.crossover()
            self.selection()
            self.fitness_val_list.append(self.get_bestFitnessValue())
        return self.fitness_val_list, self.get_bestPosition()


if __name__ == "__main__":
    with open(TestCase) as f:
        lines = f.readlines()
        for line in lines:
            line = line.replace("\t", " ").replace(
                "  ", " ").replace("\n", "").lstrip()
            i, j, w = line.split(" ")[:3]
            i = int(i)
            j = int(j)
            wij[i, j] = float(w)
            wij[j, i] = float(w)

    de = DE(N, 1000, Iter, 0, 1)
    fitVarList2, bestPos2 = de.update()
    print("DE最優位置:" + str(bestPos2))
    print("DE最優解:" + str(fitVarList2[-1]))
