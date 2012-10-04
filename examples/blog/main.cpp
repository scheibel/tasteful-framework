#include <startup>
#include <controllers/HomeController>
#include <controllers/LoginController>
#include <controllers/RegisterController>
#include <controllers/BlogPostController>
#include <controllers/AllBlogPostController>
#include <session/Session>

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
	GET("myblogposts/new") = &BlogPostController::create;
	GET("myblogposts/:id/edit") = &BlogPostController::edit;
	POST("myblogposts/save") = &BlogPostController::save;
	GET("myblogposts/:id/delete") = &BlogPostController::remove;
	DELETE("myblogposts/:id/delete") = &BlogPostController::remove;
	
	GET("blogposts") = &AllBlogPostController::index;
	GET("blogposts/:id") = &BlogPostController::show;
	
	return blog.run();
}
