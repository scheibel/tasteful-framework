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
	
	GET("blogposts") = &AllBlogPostController::index;
	
	return blog.run();
}
