#include <startup>

#include <controllers/HomeController.h>
#include <controllers/LoginController.h>
#include <controllers/RegisterController.h>
#include <controllers/BlogPostController.h>
#include <controllers/AllBlogPostController.h>
#include <controllers/SearchController.h>
#include <session/Session.h>

int main(int argc, char* argv[]) {
	WebApplication blog(argc, argv);
	QStringList args = blog.arguments();
	blog.setUpFromConfig(args.size()>=2 ? args[1] : "");
	blog.setSessionClass<Session>();
	
	ROOT = &HomeController::index;
	
	GET("login") = &LoginController::index;
	POST("login") = &LoginController::login;
	GET("logout") = &LoginController::logout;
	
	GET("register") = &RegisterController::index;
	POST("register") = &RegisterController::signup;
	
	GET("myblogposts") = &BlogPostController::index;
	GET("myblogposts/:id") = &BlogPostController::show;
	GET("myblogposts/new") = &BlogPostController::create;
	GET("myblogposts/:id/edit") = &BlogPostController::edit;
	POST("myblogposts/save") = &BlogPostController::save;
	GET("myblogposts/:id/delete") = &BlogPostController::remove;
	DELETE("myblogposts/:id/delete") = &BlogPostController::remove;
	
	GET("blogposts") = &AllBlogPostController::index;
	GET("blogposts/:id") = &AllBlogPostController::show;
	
	GET("search") = &SearchController::index;
	GET("find/:string") = &SearchController::find;
	POST("find") = &SearchController::findPost;
	
	return blog.run();
}
