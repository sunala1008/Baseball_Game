#include <iostream>
#include <string>
#include <random>
#include <time.h>

// best practice
// refactoring
// �ְ��� ������, ó���� ������ �ڵ������ �ϴ� �� ¥������ ���� �����ؼ� ���� �ڵ�� �ٲٴ� ��.

using namespace std;

#define MaxValue 10
#define Digit 3

class Answer
{
private:
	int* nums;
	int numlen;

public:
	Answer(int len) : numlen(len)
	{
		nums = new int[len];
	}

	int& operator[](int idx) // �迭 �ε��� �����ε�
	{
		if (idx < 0 || idx >= Digit)
		{
			cout << "���� 3��" << endl;
			exit(1);
		}
		return nums[idx]; // �迭 ��Ҹ� �����ڸ� ���� ����
	}

	~Answer()
	{
		delete[]nums;
	}

	//protected override string GetPrintPrefix()
	//{
	//	return "[����]  "; // �ٲ㳢������ �κ�
	//}
};

class Guess
{
private:
	int* nums;
	int numlen;

public:
	Guess(int len) : numlen(len)
	{
		nums = new int[len];
	}
	
	int& operator[](int idx) // �迭 �ε��� �����ε�
	{
		if (idx < 0 || idx >= Digit)
		{
			cout << "���� 3��" << endl;
			exit(1);
		}
		return nums[idx]; // �迭 ��Ҹ� �����ڸ� ���� ����
	}

	~Guess()
	{
		delete[]nums;
	}

	//protected override string GetPrintPrefix()
	//{
	//	return "[����]  "; // �ٲ㳢������ �κ�
	//}
};

/*
abstract class NumberContainer
{
	protected int[] _numbers = new int[Digit];

	public int Length
	{
		get
		{
			return _numbers.Length;
		}
	}

		public int this[int digit]
		{
			get
			{
				return _numbers[digit];
			}
		}


		protected abstract string GetPrintPrefix(); // => �׷��� �߻��Լ��� ����

		public void Print() // template pattern => �̷��� ����������
		{ // �ߺ��� �ּ�ȭ �ϱ� ���ؼ�...
			Console.Write(GetPrintPrefix()); // �ٲ㳢�����ϴ� �Լ��� virtual��
			for (int i = 0; i < _numbers.Length; i++)
				Console.Write(_numbers[i] + " ");

			Console.WriteLine();
		}
};
*/

class Result
{
private:
	int _strike;
	int _ball;
	int _out;

public:
	void Calculate(Answer answer, Guess guess)
	{
		for (int i = 0; i < Digit; i++)
		{
			int j = (i + 1) % Digit;
			int k = (i + 2) % Digit;

			if (guess[i] == answer[i])
				_strike++;
			else if (guess[i] == answer[j] || guess[i] == answer[k])
				_ball++;
			else
				_out++;
		}
	}

	int getStrike()
	{
		return _strike;
	}

	int getBall()
	{
		return _ball;
	}

	int getOut()
	{
		return _out;
	}

	bool IsCorrect()
	{
		return _strike == Digit;
	}
};

int main(void)
{
	Answer answer(Digit);
	
	while (true)
	{
		srand(time(NULL));

		for (int i = 0; i < Digit; i++)
		{
			answer[i] = rand() % MaxValue;
		}

		if (answer[0] != answer[1] && answer[1] != answer[2] && answer[2] != answer[0])
			break;
	}

	cout << "���� : ";
	for (int i = 0; i < Digit; i++)
	{
		cout << answer[i] << " ";
	}

	cout << endl;

	while (true)
	{
		Guess guess(Digit);

		cout << "������ ���� 3���� �Է��ϼ���." << endl;

		for (int i = 0; i < Digit; i++)
		{
			cin >> guess[i];
		}

		cout << "���� : ";
		for (int i = 0; i < Digit; i++)
		{
			cout << guess[i] << " ";
		}

		cout << endl;

		Result result;

		result.Calculate(answer, guess);

		cout << "Strike : " << result.getStrike();
		cout << "    Ball : " << result.getBall();
		cout << "    Out  : " << result.getOut();

		if (result.IsCorrect())
			break;
	}
	
	cout << "������ �����մϴ�." << endl;
}