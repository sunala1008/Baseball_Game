#include <iostream>
#include <string>
#include <random>
#include <time.h>

// best practice
// refactoring
// 최고의 연습은, 처음엔 못생긴 코드겠지만 일단 다 짜놓고나서 차차 수정해서 예쁜 코드로 바꾸는 것.

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

	int& operator[](int idx) // 배열 인덱스 오버로딩
	{
		if (idx < 0 || idx >= Digit)
		{
			cout << "숫자 3개" << endl;
			exit(1);
		}
		return nums[idx]; // 배열 요소를 참조자를 통해 리턴
	}

	~Answer()
	{
		delete[]nums;
	}

	//protected override string GetPrintPrefix()
	//{
	//	return "[정답]  "; // 바꿔끼워지는 부분
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
	
	int& operator[](int idx) // 배열 인덱스 오버로딩
	{
		if (idx < 0 || idx >= Digit)
		{
			cout << "숫자 3개" << endl;
			exit(1);
		}
		return nums[idx]; // 배열 요소를 참조자를 통해 리턴
	}

	~Guess()
	{
		delete[]nums;
	}

	//protected override string GetPrintPrefix()
	//{
	//	return "[추측]  "; // 바꿔끼워지는 부분
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


		protected abstract string GetPrintPrefix(); // => 그래서 추상함수로 만듦

		public void Print() // template pattern => 이런게 디자인패턴
		{ // 중복을 최소화 하기 위해서...
			Console.Write(GetPrintPrefix()); // 바꿔끼워야하는 함수는 virtual로
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

	cout << "정답 : ";
	for (int i = 0; i < Digit; i++)
	{
		cout << answer[i] << " ";
	}

	cout << endl;

	while (true)
	{
		Guess guess(Digit);

		cout << "추측한 숫자 3개를 입력하세요." << endl;

		for (int i = 0; i < Digit; i++)
		{
			cin >> guess[i];
		}

		cout << "추측 : ";
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
	
	cout << "게임을 종료합니다." << endl;
}