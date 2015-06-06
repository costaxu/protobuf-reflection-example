#include "a.pb.h"
#include <stdio.h>

#include <iostream>

using namespace google::protobuf;
using namespace test;
using namespace std;
int main()
{
	Hello pb;
	const Descriptor* descriptor = pb.GetDescriptor();
	assert(descriptor!=0);
	const Reflection* reflection = pb.GetReflection();
	assert(reflection!=0);

	const FieldDescriptor* fool_field = descriptor->FindFieldByName("fool");
	assert(fool_field!=0);
	reflection->SetInt32(&pb, fool_field, 10);

	const FieldDescriptor* names_field = descriptor->FindFieldByName("names");
	assert(names_field!=0);
	reflection->AddString(&pb, names_field, "costaxu");
	reflection->AddString(&pb, names_field, "徐晓波");
	reflection->AddString(&pb, names_field, "xxb");

	const FieldDescriptor* role_field = descriptor->FindFieldByName("role");
	assert(role_field);
	/*	
	{
		Role* role = new Role;;
		
		role->set_exp(5000000000LL);
		role->set_level(1);
		role->set_role_name("无敌武将");
		reflection->SetAllocatedMessage(&pb, role, role_field);
		//pb.set_allocated_role(role);
	}
	*/
	
	
	{
		Message* role = reflection->MutableMessage(&pb, role_field);
		const Descriptor* role_desc = role->GetDescriptor();
		const Reflection* role_refl = role->GetReflection();
		assert(role_desc);
		assert(role_refl);
		const FieldDescriptor* role_exp_field = role_desc->FindFieldByName("exp");
		assert(role_exp_field);
		role_refl->SetInt64(role, role_exp_field, 50000000000);
		const FieldDescriptor* role_level_field = role_desc->FindFieldByName("level");
		assert(role_level_field);
		role_refl->SetInt32(role, role_level_field, 60);
		const FieldDescriptor* role_name_field = role_desc->FindFieldByName("role_name");
		assert(role_name_field);
		role_refl->SetString(role, role_name_field, "无敌武将");
	}
		

	const FieldDescriptor* goal_field = descriptor->FindFieldByName("goals");
	assert(goal_field);
	{
		Message* goal = reflection->AddMessage(&pb, goal_field); 	
		assert(goal);
		const Descriptor* goal_desc = goal->GetDescriptor();
		const Reflection* goal_refl = goal->GetReflection();
		assert(goal_desc);
		assert(goal_refl);
		const FieldDescriptor* goal_minute_field= goal_desc->FindFieldByName("minute");
		assert(goal_minute_field);
		goal_refl->SetInt32(goal, goal_minute_field, 10);
		const FieldDescriptor* goal_shooter_field= goal_desc->FindFieldByName("shooter");
		assert(goal_shooter_field);
		goal_refl->SetString(goal, goal_shooter_field, "messi");
	}
	{
		Message* goal = reflection->AddMessage(&pb, goal_field); 	
		assert(goal);
		const Descriptor* goal_desc = goal->GetDescriptor();
		const Reflection* goal_refl = goal->GetReflection();
		assert(goal_desc);
		assert(goal_refl);
		const FieldDescriptor* goal_minute_field= goal_desc->FindFieldByName("minute");
		assert(goal_minute_field);
		goal_refl->SetInt32(goal, goal_minute_field, 50);
		const FieldDescriptor* goal_shooter_field= goal_desc->FindFieldByName("shooter");
		assert(goal_shooter_field);
		goal_refl->SetString(goal, goal_shooter_field, "pirlo");
	}



	printf("fool: %d\n",pb.fool());
	int i = 0 ;
	for (i = 0; i < pb.names_size(); i++)
	{
		cout << pb.names(i) << endl;
	}
	const Role& role1 = pb.role();
	cout << "role.exp:" << role1.exp() << endl;
	printf("role.exp: %lld role.level:%d role.role_name:%s\n", 
			role1.exp(), role1.level(), role1.role_name().c_str());
	for (i = 0; i < pb.goals_size(); i++)
	{
		const Goal& goal = pb.goals(i);
		printf("goal minute:%d, goal shooter: %s\n", 
				goal.minute(), goal.shooter().c_str());
	}
	return 0;
}
