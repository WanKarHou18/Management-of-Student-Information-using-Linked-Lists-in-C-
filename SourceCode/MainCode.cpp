#include	<iostream>
#include 	<fstream>
#include	<string>
#include	<cstdlib>
#include	"List.h"
#include	"Student.h"

using namespace std;


bool BuildStuList(char *filename, List *list) {
	Student stu, stu0;
	string temp1, temp2;
	ifstream in;
	int count = 0, num = 0;
	in.open(filename);
	if (in.is_open()) {
		while (!in.eof()) {
			count++;

			for (int i = 0; i < 3; i++)
				in >> temp1;
			for (int i = 0; i < 7; i++)
				in >> stu.id[i];
			stu.id[7] = '\0';
			for (int i = 0; i < 2; i++)
				in >> temp1;
			in >> temp2;
			while (temp2.compare("course") != 0 && count<6) {
				if (num == 0) {
					num++;
					temp1 = temp2;
				}
				else {
					temp1 = temp1 + " " + temp2 + '\0';
				}
				in >> temp2;
			}
			temp1.copy(stu.name, temp1.size());
			in >> temp1;
			for (int i = 0; i < 2; i++)
				in >> stu.course[i];
			stu.course[2] = '\0';
			for (int i = 0; i < 3; i++)
				in >> temp1;
			for (int i = 0; i < 8; i++)
				in >> stu.phone_no[i];
			stu.phone_no[8] = '\0';
			if (list->head != NULL) {
				for (int i = 1; i <= list->count; i++) {
					list->get(i, stu0);
					if (stu.compareID(stu0))
						i = list->count + 6;
					if (!stu.compareID(stu0)) {
						if (i == list->count) {
							list->insert(i + 1, stu);
							i = list->count + 3;
						}
					}
				}
			}
			else
				list->insert(count, stu);
		}
		list->remove(count);
		in.close();
		return true;
	}
	else {
		cout << "Error in opening file";
		return false;
	}

};

bool DeleteRecord(List *list, char *id) {
	Student stu;
	Student stu0;
	string s = id;
	s.copy(stu.id, sizeof(s));
	stu.id[7] = '\0';
	for (int i = 1; i <= list->count; i++)
	{
		list->get(i, stu0);
		if (stu.compareID(stu0))
		{
			list->remove(i);
			i = list->count + 1;
		}
	}
	if (stu.compareID(stu0))
		return true;
	else
		return false;

};

bool Display(List list, int source) {
	ofstream out;
	Student stu;
	Exam e;
	Subject sub;
	char fname[256];
	Node *cur;

	if (list.empty()) {
		cout << "\nOops! Nothing to display. Sorry about that.\n";
		return false;
	}
	else {
		if (source == 1) {
			for (int i = 1; i <= list.size(); i++) {
				list.get(i, stu);
				cout << "\n\nSTUDENT " << i <<  endl;
				stu.print(cout);

				cout << "\n\nPASS EXAM RESULT" << endl;
				if (stu.exam_cnt == 0) {
					cout << "This person don't have taken any exam yet!" << endl;
				}
				else {
					for (int j = 0; j < stu.exam_cnt; j++) {
						stu.exam[j].print(cout);
					}
					cout << "\n\nSTUDENT " << i << "\n\n" << endl;
				}
			}
		}

		//if to file
		else if (source == 2) {
			if (list.empty()) {
				cout << "\nNothing to display\n";
				return false;
			}
			else {
				out.open("student_result.txt");
				if (!out) {
					cout << "\nError\n";
				}
				else {
					
					for (int i = 1; i <= list.size(); i++) {
						list.get(i, stu);
						out << "\n\nSTUDENT " << i << endl;
						stu.print(out);

						out << "\n\nPASS EXAM RESULT" << endl;
						if (stu.exam_cnt == 0) {
							out << "This person don't have taken any exam yet!" << endl;
						}
						else {
							for (int j = 0; j < stu.exam_cnt; j++) {
								stu.exam[j].print(out);
							}
							out << "\n\nSTUDENT " << i << "\n\n" << endl;
						}


					}

				}

			}
			out.close();
			return true;
		}

	}
	return true;
};

bool InsertResult(char *filename, List *list) {

	ifstream in;
	Student stu;
	char stuid[256];
	Exam exam;
	int stuidposition;
	bool found = false;
	Node * cur;

	in.open(filename);

	if (!in) {
		cout << "\nError. Cannot find the file\n" << endl;
		return false;
	}

	else {
		while (!in.eof()) {

			in >> stu.id;
			cur = list->head;
			while (cur != NULL) {
				found = false;
				if (strcmp(stu.id, cur->item.id) == 0)
				{
					in >> exam.trimester >> exam.year >> exam.numOfSubjects;
					for (int i = 0; i < exam.numOfSubjects; i++) {
						in >> exam.sub[i].subject_code;
						in >> exam.sub[i].subject_name;
						in >> exam.sub[i].credit_hours;
						in >> exam.sub[i].marks;
					}
					exam.calculateGPA();
					cur->item.exam[cur->item.exam_cnt] = exam;
					cur->item.exam_cnt++;
					cur->item.calculateCurrentCGPA();
					found = true;
					break;
				}
				cur = cur->next;
			}

		}

		in.close();
		cout << "\nSuccessfully Inserted!\n";
		return true;
	}

};

bool printStatistic(List list) {
	Student stu;
	int totalstu = list.count;
	int cs = 0, ia = 0, ib = 0, cn = 0, ct = 0;
	double avrcre = 0, totalcre = 0, examcnt = 0, avrsub = 0, avrsubN = 0, avrcgpa = 0;
	if (list.head == NULL) {
		return false;
	}
	for (int i = 1; i <= list.count; i++) {
		list.get(i, stu);
		if (strcmp(stu.course, "CS") == 0)
			cs++;
		else if (strcmp(stu.course, "IA") == 0)
			ia++;
		else if (strcmp(stu.course, "IB") == 0)
			ib++;
		else if (strcmp(stu.course, "CN") == 0)
			cn++;
		else if (strcmp(stu.course, "CT") == 0)
			ct++;
		avrcgpa = stu.current_cgpa + avrcgpa;
		if (stu.exam_cnt > 0) {
			totalcre = stu.totalCreditsEarned;
			examcnt = stu.exam_cnt;
			avrcre = (totalcre) / (examcnt);
		}
		if (stu.exam_cnt < 1)
			avrcre = 0;
		avrcre = avrcre + avrcre;
		avrcre = 0;
		for (int i = 0; i < stu.exam_cnt; i++) {
			avrsub = stu.exam[i].numOfSubjects + avrsub;
			if (i + 1 == stu.exam_cnt) {
				avrsub = avrsub / stu.exam_cnt;
				avrsubN = avrsubN + avrsub;
			}
		}
	}
	avrcgpa = avrcgpa / totalstu;
	avrcre = avrcre / totalstu;
	avrsubN = avrsubN / totalstu;
	cout << "Total Student: " << totalstu << endl;
	cout << "CS Student: " << cs << endl;
	cout << "IA Student: " << ia << endl;
	cout << "IB Student: " << ib << endl;
	cout << "CN Student: " << cn << endl;
	cout << "CT Student: " << ct << endl;
	cout << "Average CGPA: " << avrcgpa << endl;
	cout << "Average subject taken per semester: " << avrsubN << endl;
	cout << "Average credit earned per semester: " << avrcre << endl;
	return true;
};

bool findEligibleFYPStudent(List list, List *fyplist) {
	Student student;

	if (list.head == NULL)
	{
		return false;
	}
	else
	{
		for (int i = 1; i <= list.count; i++)
		{
			list.get(i, student);
			for (int j = 0; j <= sizeof(student.exam); j++)
			{
				for (int k = 0; k < sizeof(student.exam[j].sub); k++)
				{
					if (strcmp(student.exam[j].sub[k].subject_code, "UCCD2502") == 0 && student.exam[j].sub[k].getGrade() != "F")
					{
						for (int l = 0; l < sizeof(student.exam[j].sub); l++) {
							if (strcmp(student.exam[j].sub[l].subject_code, "UCCD2513") == 0 && student.exam[j].sub[l].getGrade() != "F" && (student.totalCreditsEarned >= 30))
								fyplist->insert(i, student);
						}
					}
				}
			}
		}
	}
	if (fyplist == NULL)
	{
		cout << "There is no student that is eligible to take FYP" << endl;
		return true;
	}
	else
	{
		return true;
	}
};

bool identifyGoodPoorStudent(List list1, List *goodList, List *poorList) {
	Student stu;
	int list_count;
	int fail_sem = 0;
	int fail_subject = 0;

	list_count = list1.count;

	if (list1.head != NULL)
	{
		for (int i = 1; i <= list1.count; i++)
		{

			list1.get(i, stu);
			if (stu.exam_cnt < 3)
			{
				for (int j = 0; j<stu.exam_cnt; j++)
				{
					if ((stu.exam[j].gpa <= 2.000) && (stu.current_cgpa <= 2.000))
					{
						fail_sem = fail_sem + 1;

						if (fail_sem >= 3)
						{
							poorList->insert(i, stu);
						}
					}

				}

				for (int k = 0; k <stu.exam_cnt; k++)
				{
					if ((stu.current_cgpa >= 3.50) && (stu.exam[k].gpa >= 3.5000))
					{
						for (int a = 0; a<stu.exam_cnt; a++)
						{
							if (stu.exam[k].sub[a].getGrade() == "F")
							{
								fail_subject = 1;
							}
						}
						if (fail_subject<1)
						{
							goodList->insert(i, stu);
						}

					}
				}

			}
			break;
		}

		if (goodList == NULL)
		{
			cout << "There is no student in good list" << endl;
			return true;
		}
		else if (poorList == NULL)
		{
			cout << "There is no student in bad list " << endl;
			return true;
		}
		else
		{
			return true;
		}
	}

	else
	{
		return false;
	}

};

int menu() {
	cout << "enter Choice";
	int choice;
	cin >> choice;
	return choice;
};

using namespace std;


int main() {
	
	List list;
	List *list1 = new List();
	List *FYPlist = new List();
	List *goodList = new List();
	List *poorList = new List();

	Student stu;
	Exam exam;
	char *filename1 = "student.txt";
	char *filename2 = "exam.txt";
	int option, source;
	char id;
	int c[5] = { 0, 0, 0, 0, 0 };

	do {
		cout << "\n\n\t\t\tUTAR MY CHOICE!\t\t\t" << endl;
		cout << "\n\n---------------------------***MENU***-------------------------------\n\n" << endl;
		cout << "\n1.Read File";
		cout << "\n2.Delete Record";
		cout << "\n3.Insert Past Exam Result";
		cout << "\n4.Display Output";
		cout << "\n5.Print Statistic";
		cout << "\n6.Find Eligible FYP Student";
		cout << "\n7.Identify Good and Poor Result Student";
		cout << "\n8.Exit";
		cout << "\n\n---------------------------------------------------------------------\n\n" << endl;
		cout << "\nSelect to Proceed: ";
		cin >> option;

		switch (option)
		{
		case 1: if (BuildStuList(filename1, &list) == 1) {
			cout << "File read succefully.";
		};
			break;
		case 2: if (list.empty()) {
			cout << "\nIt is an empty list!\n";
		}
				else {
					cout << "Insert ID";
					cin >> &id;
					DeleteRecord(&list, &id);
				}
				break;
		case 3: InsertResult(filename2, &list);
			break;
		case 4:
			cout << "\nChoose a location to display your file: ";
			cout << "\n1.On screen\t\t";
			cout << "2.Into file\n";
			cin >> source;
			Display(list, source);
			break;
		case 5: printStatistic(list);
			break;
		case 6: findEligibleFYPStudent(*list1, FYPlist);
			if (!FYPlist->empty()) {
				Display(*FYPlist, 1);
			}
			else {
				cout << "\nThere is no student that is eligible to take FYP.";
			}
			break;
		case 7: identifyGoodPoorStudent(*list1, goodList, poorList);

			if (!goodList->empty()) {
				Display(*goodList, 1);
			}
			else {
				cout << "\nThere is no student in good list.";
			}

			if (!poorList->empty()) {

				Display(*poorList, 1);
			}
			else {

				cout << "\nThere is no student in poor list.";
			}
			break;
		case 8: exit(1);
			break;

		default:
			cout << "\nInvalid option. Please try again.\n";
		}
	} while (true);


	system("pause");
	return 0;
}