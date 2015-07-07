#include <gtest/gtest.h>
#include <TextureUnitManager.h>
TEST(TextureUnitManager,testGetUnits)
{
   TextureUnit unit1 = TextureUnitManager::requestTextureUnit();
   EXPECT_EQ(unit1.getTexUnit(), 0);
   EXPECT_EQ(unit1.getGlUnit(), GL_TEXTURE0);
   TextureUnit unit2 = TextureUnitManager::requestTextureUnit();
   EXPECT_EQ(unit2.getTexUnit(), 1);
   EXPECT_EQ(unit2.getGlUnit(), GL_TEXTURE1);
   unit1.release();

   EXPECT_EQ(unit1.getTexUnit(), -1);
   TextureUnit unit3 = TextureUnitManager::requestTextureUnit();
   EXPECT_EQ(unit3.getTexUnit(), 0);
   TextureUnit unit4 = TextureUnitManager::requestTextureUnit();
   EXPECT_EQ(unit4.getTexUnit(), 2);

   unit2.release();
   unit3.release();
   unit4.release();
}
