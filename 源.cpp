#include <stdio.h>
#include "源.h"

/*	事件event，	  *
*	参数parameters*/

//管理端密码
int event_mpassword = 123987;

//Click on the product, parameters:click_location, products
int event_click_product = 1;
int click_location = 0;
char products[] = "right";
//good, right, all, unapproved, approved, reduced_prices, confirm

//review procdts(approve page),parameters:click_location, products
int event_approved = 2;
int event_unapproved = 3;

//seclect products,parameters:click_location, products
int event_good = 4;
int event_good_delete = 5;

//product page
int event_delete_product = 6;
//parameters:comment_click_location, product
int event_click_user = 7;
int comment_click_location = 0;

//user page,
int event_comment_permission = 8;
int event_recomment_permission = 9;

//comment page,parameters:product
int event_click_comment = 10;

/*	管理端接口			*
*	Management interface*/

//判断密码是否正确Determine if the password is correct
bool true_mpassword(int mcode);

//精选商品Selected products
int good_products();
bool good_products_full();
int good_products_add(int product);
int good_products_delete(int product);
//已审核商品Approved products
int approved_products();

//approve page
//read data
int all_products();
int unapproved_products();

//seclect page
int  reduced_prices_products();

//product page
int price_trend_product(int product);
int not_worth_product(int product);
int worth_product(int product);

//Click on the product to confirm it
int product_confirm(int click_location, char* products);

//modify data:product商品
int product_approved(int product);
int product_delete(int product);

//Click on the user to confirm it
int user_confirm(int comment_click_location, int product);

//modify data:user用户
int user_comment(int user);
int user_recomment(int user);

//comment
int product_comment(int product);

//refresh data
void refresh_data()
{
	//Need to pack as JSON for front end!!!
	//frist page
	good_products();
	approved_products();

	//approve page
	all_products();
	unapproved_products();

	//Selected products page
	reduced_prices_products();
}

int main(int mevent) {
	//mevent表示传入的事件
	bool code;

	while (1) {
		//密码登录
		if (mevent == event_mpassword)
		{
			if (true_mpassword(event_mpassword)) {
				code = true;
			}
			else {
				//error = "密码错误"
				code = false;
				break;
			}
		}
	}

	//Initialized Data
	if (code) {
		refresh_data();
	}

	int product, user, comment;
	while (code)
	{
		if (mevent == event_click_product)
		{
			//click_location and goods need from event_click_good
			product = product_confirm(click_location, products);
			price_trend_product(product);
			//not_worth_good(product);管理端不需要
			//worth_good(product);
		}
		if (mevent == event_approved)
		{
			product = product_confirm(click_location, products);
			product_approved(product);
			//refresh data 刷新数据
			refresh_data();
		}
		if (mevent == event_unapproved)
		{
			product = product_confirm(click_location, products);
			product_delete(product);
			//refresh data 刷新数据
			refresh_data();
		}
		if (mevent == event_good)
		{
			if (!good_products_full())
			{
				product = product_confirm(click_location, products);
				good_products_add(product);
				//refresh data 刷新数据
				refresh_data();
			}
			else {
				//"error:good_goods is full/n"
			}
		}
		if (mevent == event_good_delete)
		{
			product = product_confirm(click_location, products);
			good_products_delete(product);
			//refresh data 刷新数据
			refresh_data();
		}
		if (mevent == event_delete_product)
		{
			product = product_confirm(click_location, products);
			product_delete(product);
			//refresh data 刷新数据
			refresh_data();
		}
		if (mevent == event_click_user)
		{
			user = user_confirm(comment_click_location, product);
		}
		if (mevent == event_comment_permission)
		{
			user_comment(user);
		}
		if (mevent == event_recomment_permission)
		{
			user_recomment(user);
		}
		if (mevent == event_click_comment)
		{
			comment = product_comment(product);
		}
	}
}